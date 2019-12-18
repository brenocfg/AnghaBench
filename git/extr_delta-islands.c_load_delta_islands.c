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
struct repository {int dummy; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  deduplicate_islands (struct repository*) ; 
 int /*<<< orphan*/  find_island_for_ref ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  island_config_callback ; 
 int island_counter ; 
 int /*<<< orphan*/  island_marks ; 
 int /*<<< orphan*/  kh_init_oid_map () ; 
 int /*<<< orphan*/  kh_init_str () ; 
 int /*<<< orphan*/  remote_islands ; 
 int /*<<< orphan*/  stderr ; 

void load_delta_islands(struct repository *r, int progress)
{
	island_marks = kh_init_oid_map();
	remote_islands = kh_init_str();

	git_config(island_config_callback, NULL);
	for_each_ref(find_island_for_ref, NULL);
	deduplicate_islands(r);

	if (progress)
		fprintf(stderr, _("Marked %d islands, done.\n"), island_counter);
}