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
struct view {int /*<<< orphan*/  lock; int /*<<< orphan*/  local_zones; scalar_t__ isfirst; } ;
struct config_view {struct config_strlist* local_zones_nodefault; int /*<<< orphan*/ * local_data; int /*<<< orphan*/ * local_zones; scalar_t__ isfirst; int /*<<< orphan*/  name; struct config_view* next; } ;
struct config_strlist {char* str; struct config_strlist* next; } ;
struct config_file {int local_zones_disable_default; int /*<<< orphan*/ * local_zones; struct config_strlist* local_zones_nodefault; int /*<<< orphan*/ * local_data; struct config_view* views; } ;
typedef  int /*<<< orphan*/  lz_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  cfg_str2list_insert (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  local_zones_apply_cfg (int /*<<< orphan*/ ,struct config_file*) ; 
 int /*<<< orphan*/  local_zones_create () ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  memset (struct config_file*,int /*<<< orphan*/ ,int) ; 
 char* strdup (char*) ; 
 struct view* views_enter_view_name (struct views*,int /*<<< orphan*/ ) ; 

int 
views_apply_cfg(struct views* vs, struct config_file* cfg)
{
	struct config_view* cv;
	struct view* v;
	struct config_file lz_cfg;
	/* Check existence of name in first view (last in config). Rest of
	 * views are already checked when parsing config. */
	if(cfg->views && !cfg->views->name) {
		log_err("view without a name");
		return 0;
	}
	for(cv = cfg->views; cv; cv = cv->next) {
		/* create and enter view */
		if(!(v = views_enter_view_name(vs, cv->name)))
			return 0;
		v->isfirst = cv->isfirst;
		if(cv->local_zones || cv->local_data) {
			if(!(v->local_zones = local_zones_create())){
				lock_rw_unlock(&v->lock);
				return 0;
			}
			memset(&lz_cfg, 0, sizeof(lz_cfg));
			lz_cfg.local_zones = cv->local_zones;
			lz_cfg.local_data = cv->local_data;
			lz_cfg.local_zones_nodefault =
				cv->local_zones_nodefault;
			if(v->isfirst) {
				/* Do not add defaults to view-specific
				 * local-zone when global local zone will be
				 * used. */
				struct config_strlist* nd;
				lz_cfg.local_zones_disable_default = 1;
				/* Add nodefault zones to list of zones to add,
				 * so they will be used as if they are
				 * configured as type transparent */
				for(nd = cv->local_zones_nodefault; nd;
					nd = nd->next) {
					char* nd_str, *nd_type;
					nd_str = strdup(nd->str);
					if(!nd_str) {
						log_err("out of memory");
						lock_rw_unlock(&v->lock);
						return 0;
					}
					nd_type = strdup("nodefault");
					if(!nd_type) {
						log_err("out of memory");
						free(nd_str);
						lock_rw_unlock(&v->lock);
						return 0;
					}
					if(!cfg_str2list_insert(
						&lz_cfg.local_zones, nd_str,
						nd_type)) {
						log_err("failed to insert "
							"default zones into "
							"local-zone list");
						free(nd_str);
						free(nd_type);
						lock_rw_unlock(&v->lock);
						return 0;
					}
				}
			}
			if(!local_zones_apply_cfg(v->local_zones, &lz_cfg)){
				lock_rw_unlock(&v->lock);
				return 0;
			}
			/* local_zones, local_zones_nodefault and local_data 
			 * are free'd from config_view by local_zones_apply_cfg.
			 * Set pointers to NULL. */
			cv->local_zones = NULL;
			cv->local_data = NULL;
			cv->local_zones_nodefault = NULL;
		}
		lock_rw_unlock(&v->lock);
	}
	return 1;
}