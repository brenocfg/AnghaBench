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
struct infra_cache {int /*<<< orphan*/  domain_limits; } ;
struct config_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  infra_ratelimit_cfg_insert (struct infra_cache*,struct config_file*) ; 
 int /*<<< orphan*/  name_tree_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name_tree_init_parents (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
setup_domain_limits(struct infra_cache* infra, struct config_file* cfg)
{
	name_tree_init(&infra->domain_limits);
	if(!infra_ratelimit_cfg_insert(infra, cfg)) {
		return 0;
	}
	name_tree_init_parents(&infra->domain_limits);
	return 1;
}