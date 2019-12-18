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
struct eap_sim_reauth {struct eap_sim_reauth* reauth_id; struct eap_sim_reauth* permanent; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct eap_sim_reauth*) ; 

__attribute__((used)) static void eap_sim_db_free_reauth(struct eap_sim_reauth *r)
{
	os_free(r->permanent);
	os_free(r->reauth_id);
	os_free(r);
}