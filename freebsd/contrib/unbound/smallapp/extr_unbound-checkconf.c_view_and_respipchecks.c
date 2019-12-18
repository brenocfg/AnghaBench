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
struct views {int dummy; } ;
struct respip_set {int dummy; } ;
struct config_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  respip_global_apply_cfg (struct respip_set*,struct config_file*) ; 
 struct respip_set* respip_set_create () ; 
 int /*<<< orphan*/  respip_set_delete (struct respip_set*) ; 
 int /*<<< orphan*/  respip_views_apply_cfg (struct views*,struct config_file*,int*) ; 
 int /*<<< orphan*/  views_apply_cfg (struct views*,struct config_file*) ; 
 struct views* views_create () ; 
 int /*<<< orphan*/  views_delete (struct views*) ; 

__attribute__((used)) static void
view_and_respipchecks(struct config_file* cfg)
{
	struct views* views = NULL;
	struct respip_set* respip = NULL;
	int ignored = 0;
	if(!(views = views_create()))
		fatal_exit("Could not create views: out of memory");
	if(!(respip = respip_set_create()))
		fatal_exit("Could not create respip set: out of memory");
	if(!views_apply_cfg(views, cfg))
		fatal_exit("Could not set up views");
	if(!respip_global_apply_cfg(respip, cfg))
		fatal_exit("Could not setup respip set");
	if(!respip_views_apply_cfg(views, cfg, &ignored))
		fatal_exit("Could not setup per-view respip sets");
	views_delete(views);
	respip_set_delete(respip);
}