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
struct infra_cache {int /*<<< orphan*/  client_ip_rates; int /*<<< orphan*/  domain_limits; int /*<<< orphan*/  domain_rates; int /*<<< orphan*/  hosts; } ;

/* Variables and functions */
 int /*<<< orphan*/  domain_limit_free ; 
 int /*<<< orphan*/  free (struct infra_cache*) ; 
 int /*<<< orphan*/  slabhash_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void 
infra_delete(struct infra_cache* infra)
{
	if(!infra)
		return;
	slabhash_delete(infra->hosts);
	slabhash_delete(infra->domain_rates);
	traverse_postorder(&infra->domain_limits, domain_limit_free, NULL);
	slabhash_delete(infra->client_ip_rates);
	free(infra);
}