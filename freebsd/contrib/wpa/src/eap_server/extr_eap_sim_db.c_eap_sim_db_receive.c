#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct eap_sim_db_data {int /*<<< orphan*/ * get_complete_cb; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  eap_sim_db_aka_resp_auth (struct eap_sim_db_data*,char*,char*) ; 
 int /*<<< orphan*/  eap_sim_db_sim_resp_auth (struct eap_sim_db_data*,char*,char*) ; 
 char* os_strchr (char*,char) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_sim_db_receive(int sock, void *eloop_ctx, void *sock_ctx)
{
	struct eap_sim_db_data *data = eloop_ctx;
	char buf[1000], *pos, *cmd, *imsi;
	int res;

	res = recv(sock, buf, sizeof(buf) - 1, 0);
	if (res < 0)
		return;
	buf[res] = '\0';
	wpa_hexdump_ascii_key(MSG_MSGDUMP, "EAP-SIM DB: Received from an "
			      "external source", (u8 *) buf, res);
	if (res == 0)
		return;

	if (data->get_complete_cb == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-SIM DB: No get_complete_cb "
			   "registered");
		return;
	}

	/* <cmd> <IMSI> ... */

	cmd = buf;
	pos = os_strchr(cmd, ' ');
	if (pos == NULL)
		goto parse_fail;
	*pos = '\0';
	imsi = pos + 1;
	pos = os_strchr(imsi, ' ');
	if (pos == NULL)
		goto parse_fail;
	*pos = '\0';
	wpa_printf(MSG_DEBUG, "EAP-SIM DB: External response=%s for IMSI %s",
		   cmd, imsi);

	if (os_strcmp(cmd, "SIM-RESP-AUTH") == 0)
		eap_sim_db_sim_resp_auth(data, imsi, pos + 1);
	else if (os_strcmp(cmd, "AKA-RESP-AUTH") == 0)
		eap_sim_db_aka_resp_auth(data, imsi, pos + 1);
	else
		wpa_printf(MSG_INFO, "EAP-SIM DB: Unknown external response "
			   "'%s'", cmd);
	return;

parse_fail:
	wpa_printf(MSG_DEBUG, "EAP-SIM DB: Failed to parse response string");
}