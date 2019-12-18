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
struct repository {TYPE_1__* parsed_objects; } ;
struct TYPE_2__ {int is_shallow; int /*<<< orphan*/  shallow_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  git_path_shallow (struct repository*) ; 
 int /*<<< orphan*/  stat_validity_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_shallow_file_for_update(struct repository *r)
{
	if (r->parsed_objects->is_shallow == -1)
		BUG("shallow must be initialized by now");

	if (!stat_validity_check(r->parsed_objects->shallow_stat,
				 git_path_shallow(r)))
		die("shallow file has changed since we read it");
}