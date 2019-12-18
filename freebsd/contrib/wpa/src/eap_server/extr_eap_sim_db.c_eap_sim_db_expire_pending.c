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
struct eap_sim_db_pending {int dummy; } ;
struct eap_sim_db_data {int /*<<< orphan*/  eap_sim_db_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_sim_db_query_timeout ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eap_sim_db_data*,struct eap_sim_db_pending*) ; 

__attribute__((used)) static void eap_sim_db_expire_pending(struct eap_sim_db_data *data,
				      struct eap_sim_db_pending *entry)
{
	eloop_register_timeout(data->eap_sim_db_timeout, 0,
			       eap_sim_db_query_timeout, data, entry);
}