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
struct config_strlist {int dummy; } ;
struct config_file {int dummy; } ;

/* Variables and functions */
 char* config_collate_cat (struct config_strlist*) ; 
 int /*<<< orphan*/  config_delstrlist (struct config_strlist*) ; 
 int config_get_option_list (struct config_file*,char const*,struct config_strlist**) ; 

int
config_get_option_collate(struct config_file* cfg, const char* opt, char** str)
{
	struct config_strlist* list = NULL;
	int r;
	*str = NULL;
	if((r = config_get_option_list(cfg, opt, &list)) != 0)
		return r;
	*str = config_collate_cat(list);
	config_delstrlist(list);
	if(!*str) return 2;
	return 0;
}