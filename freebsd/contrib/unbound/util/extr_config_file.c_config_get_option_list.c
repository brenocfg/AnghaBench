#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct config_strlist {int dummy; } ;
struct config_file {int dummy; } ;
struct TYPE_2__ {struct config_strlist* first; } ;
struct config_collate_arg {TYPE_1__ list; scalar_t__ status; } ;
typedef  int /*<<< orphan*/  m ;

/* Variables and functions */
 int /*<<< orphan*/  config_collate_func ; 
 int /*<<< orphan*/  config_delstrlist (struct config_strlist*) ; 
 int /*<<< orphan*/  config_get_option (struct config_file*,char const*,int /*<<< orphan*/ ,struct config_collate_arg*) ; 
 int /*<<< orphan*/  memset (struct config_collate_arg*,int /*<<< orphan*/ ,int) ; 

int config_get_option_list(struct config_file* cfg, const char* opt,
	struct config_strlist** list)
{
	struct config_collate_arg m;
	memset(&m, 0, sizeof(m));
	*list = NULL;
	if(!config_get_option(cfg, opt, config_collate_func, &m))
		return 1;
	if(m.status) {
		config_delstrlist(m.list.first);
		return 2;
	}
	*list = m.list.first;
	return 0;
}