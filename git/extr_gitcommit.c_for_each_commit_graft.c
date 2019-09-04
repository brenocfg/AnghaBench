#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int (* each_commit_graft_fn ) (int /*<<< orphan*/ ,void*) ;
struct TYPE_4__ {TYPE_1__* parsed_objects; } ;
struct TYPE_3__ {int grafts_nr; int /*<<< orphan*/ * grafts; } ;

/* Variables and functions */
 TYPE_2__* the_repository ; 

int for_each_commit_graft(each_commit_graft_fn fn, void *cb_data)
{
	int i, ret;
	for (i = ret = 0; i < the_repository->parsed_objects->grafts_nr && !ret; i++)
		ret = fn(the_repository->parsed_objects->grafts[i], cb_data);
	return ret;
}