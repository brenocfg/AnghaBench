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
struct eap_sm {int dummy; } ;
struct eap_sim_data {size_t num_chal; int /*<<< orphan*/ * rand; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  GSM_RAND_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_sm_request_sim (struct eap_sm*,char*) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_sim_ext_sim_req(struct eap_sm *sm, struct eap_sim_data *data)
{
	char req[200], *pos, *end;
	size_t i;

	wpa_printf(MSG_DEBUG, "EAP-SIM: Use external SIM processing");
	pos = req;
	end = pos + sizeof(req);
	pos += os_snprintf(pos, end - pos, "GSM-AUTH");
	for (i = 0; i < data->num_chal; i++) {
		pos += os_snprintf(pos, end - pos, ":");
		pos += wpa_snprintf_hex(pos, end - pos, data->rand[i],
					GSM_RAND_LEN);
	}

	eap_sm_request_sim(sm, req);
	return 1;
}