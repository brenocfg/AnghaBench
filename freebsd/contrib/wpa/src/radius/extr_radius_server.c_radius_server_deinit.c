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
struct radius_server_data {scalar_t__ auth_sock; scalar_t__ acct_sock; scalar_t__ db; struct radius_server_data* t_c_server_url; struct radius_server_data* hs20_sim_provisioning_url; struct radius_server_data* subscr_remediation_url; struct radius_server_data* dump_msk_file; struct radius_server_data* eap_req_id_text; struct radius_server_data* eap_fast_a_id_info; struct radius_server_data* eap_fast_a_id; struct radius_server_data* pac_opaque_encr_key; int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (scalar_t__) ; 
 int /*<<< orphan*/  os_free (struct radius_server_data*) ; 
 int /*<<< orphan*/  radius_server_erp_flush (struct radius_server_data*) ; 
 int /*<<< orphan*/  radius_server_free_clients (struct radius_server_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_close (scalar_t__) ; 

void radius_server_deinit(struct radius_server_data *data)
{
	if (data == NULL)
		return;

	if (data->auth_sock >= 0) {
		eloop_unregister_read_sock(data->auth_sock);
		close(data->auth_sock);
	}

	if (data->acct_sock >= 0) {
		eloop_unregister_read_sock(data->acct_sock);
		close(data->acct_sock);
	}

	radius_server_free_clients(data, data->clients);

	os_free(data->pac_opaque_encr_key);
	os_free(data->eap_fast_a_id);
	os_free(data->eap_fast_a_id_info);
	os_free(data->eap_req_id_text);
#ifdef CONFIG_RADIUS_TEST
	os_free(data->dump_msk_file);
#endif /* CONFIG_RADIUS_TEST */
	os_free(data->subscr_remediation_url);
	os_free(data->hs20_sim_provisioning_url);
	os_free(data->t_c_server_url);

#ifdef CONFIG_SQLITE
	if (data->db)
		sqlite3_close(data->db);
#endif /* CONFIG_SQLITE */

	radius_server_erp_flush(data);

	os_free(data);
}