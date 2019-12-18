#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_chal; int /*<<< orphan*/ * rand; int /*<<< orphan*/ * sres; int /*<<< orphan*/ * kc; } ;
struct TYPE_4__ {TYPE_1__ sim; } ;
struct eap_sim_db_pending {int /*<<< orphan*/  cb_session_ctx; int /*<<< orphan*/  state; TYPE_2__ u; } ;
struct eap_sim_db_data {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* get_complete_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_SIM_KC_LEN ; 
 int EAP_SIM_MAX_CHAL ; 
 int /*<<< orphan*/  EAP_SIM_SRES_LEN ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  GSM_RAND_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  eap_sim_db_add_pending (struct eap_sim_db_data*,struct eap_sim_db_pending*) ; 
 int /*<<< orphan*/  eap_sim_db_free_pending (struct eap_sim_db_data*,struct eap_sim_db_pending*) ; 
 struct eap_sim_db_pending* eap_sim_db_get_pending (struct eap_sim_db_data*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ hexstr2bin (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* os_strchr (char*,char) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_sim_db_sim_resp_auth(struct eap_sim_db_data *data,
				     const char *imsi, char *buf)
{
	char *start, *end, *pos;
	struct eap_sim_db_pending *entry;
	int num_chal;

	/*
	 * SIM-RESP-AUTH <IMSI> Kc(i):SRES(i):RAND(i) ...
	 * SIM-RESP-AUTH <IMSI> FAILURE
	 * (IMSI = ASCII string, Kc/SRES/RAND = hex string)
	 */

	entry = eap_sim_db_get_pending(data, imsi, 0);
	if (entry == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-SIM DB: No pending entry for the "
			   "received message found");
		return;
	}

	start = buf;
	if (os_strncmp(start, "FAILURE", 7) == 0) {
		wpa_printf(MSG_DEBUG, "EAP-SIM DB: External server reported "
			   "failure");
		entry->state = FAILURE;
		eap_sim_db_add_pending(data, entry);
		data->get_complete_cb(data->ctx, entry->cb_session_ctx);
		return;
	}

	num_chal = 0;
	while (num_chal < EAP_SIM_MAX_CHAL) {
		end = os_strchr(start, ' ');
		if (end)
			*end = '\0';

		pos = os_strchr(start, ':');
		if (pos == NULL)
			goto parse_fail;
		*pos = '\0';
		if (hexstr2bin(start, entry->u.sim.kc[num_chal],
			       EAP_SIM_KC_LEN))
			goto parse_fail;

		start = pos + 1;
		pos = os_strchr(start, ':');
		if (pos == NULL)
			goto parse_fail;
		*pos = '\0';
		if (hexstr2bin(start, entry->u.sim.sres[num_chal],
			       EAP_SIM_SRES_LEN))
			goto parse_fail;

		start = pos + 1;
		if (hexstr2bin(start, entry->u.sim.rand[num_chal],
			       GSM_RAND_LEN))
			goto parse_fail;

		num_chal++;
		if (end == NULL)
			break;
		else
			start = end + 1;
	}
	entry->u.sim.num_chal = num_chal;

	entry->state = SUCCESS;
	wpa_printf(MSG_DEBUG, "EAP-SIM DB: Authentication data parsed "
		   "successfully - callback");
	eap_sim_db_add_pending(data, entry);
	data->get_complete_cb(data->ctx, entry->cb_session_ctx);
	return;

parse_fail:
	wpa_printf(MSG_DEBUG, "EAP-SIM DB: Failed to parse response string");
	eap_sim_db_free_pending(data, entry);
}