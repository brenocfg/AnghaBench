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
struct repository {TYPE_1__* parsed_objects; } ;
struct TYPE_4__ {int /*<<< orphan*/  have_repository; } ;
struct TYPE_3__ {int commit_graft_prepared; } ;

/* Variables and functions */
 char* get_graft_file (struct repository*) ; 
 int /*<<< orphan*/  is_repository_shallow (struct repository*) ; 
 int /*<<< orphan*/  read_graft_file (struct repository*,char*) ; 
 TYPE_2__* startup_info ; 

void prepare_commit_graft(struct repository *r)
{
	char *graft_file;

	if (r->parsed_objects->commit_graft_prepared)
		return;
	if (!startup_info->have_repository)
		return;

	graft_file = get_graft_file(r);
	read_graft_file(r, graft_file);
	/* make sure shallows are read */
	is_repository_shallow(r);
	r->parsed_objects->commit_graft_prepared = 1;
}