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
struct iter_hints {int dummy; } ;
struct config_strlist {char* str; struct config_strlist* next; } ;
struct config_file {scalar_t__* chrootdir; struct config_strlist* root_hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (char*) ; 
 int /*<<< orphan*/  read_root_hints (struct iter_hints*,char*) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 
 scalar_t__ strncmp (char*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
read_root_hints_list(struct iter_hints* hints, struct config_file* cfg)
{
	struct config_strlist* p;
	for(p = cfg->root_hints; p; p = p->next) {
		log_assert(p->str);
		if(p->str && p->str[0]) {
			char* f = p->str;
			if(cfg->chrootdir && cfg->chrootdir[0] &&
				strncmp(p->str, cfg->chrootdir, 
				strlen(cfg->chrootdir)) == 0)
				f += strlen(cfg->chrootdir);
			if(!read_root_hints(hints, f))
				return 0;
		}
	}
	return 1;
}