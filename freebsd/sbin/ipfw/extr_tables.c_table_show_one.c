#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tablename; } ;
typedef  TYPE_1__ ipfw_xtable_info ;
typedef  int /*<<< orphan*/  ipfw_obj_header ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int table_do_get_list (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  table_show_list (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
table_show_one(ipfw_xtable_info *i, void *arg)
{
	ipfw_obj_header *oh;
	int error;
	int is_all;

	is_all = arg == NULL ? 0 : 1;

	if ((error = table_do_get_list(i, &oh)) != 0) {
		err(EX_OSERR, "Error requesting table %s list", i->tablename);
		return (error);
	}

	table_show_list(oh, is_all);

	free(oh);
	return (0);	
}