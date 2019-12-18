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
typedef  int /*<<< orphan*/  u16 ;
struct eap_sim_reauth {int /*<<< orphan*/  mk; } ;
struct eap_sim_db_data {scalar_t__ sqlite_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_SIM_MK_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int db_add_reauth (struct eap_sim_db_data*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct eap_sim_reauth* eap_sim_db_add_reauth_data (struct eap_sim_db_data*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*,char const*) ; 

int eap_sim_db_add_reauth(struct eap_sim_db_data *data, const char *permanent,
			  char *reauth_id, u16 counter, const u8 *mk)
{
	struct eap_sim_reauth *r;

	wpa_printf(MSG_DEBUG, "EAP-SIM DB: Add reauth_id '%s' for permanent "
		   "identity '%s'", reauth_id, permanent);

#ifdef CONFIG_SQLITE
	if (data->sqlite_db)
		return db_add_reauth(data, permanent, reauth_id, counter, mk,
				     NULL, NULL, NULL);
#endif /* CONFIG_SQLITE */
	r = eap_sim_db_add_reauth_data(data, permanent, reauth_id, counter);
	if (r == NULL)
		return -1;

	os_memcpy(r->mk, mk, EAP_SIM_MK_LEN);

	return 0;
}