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
struct printc {int dummy; } ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  be ; 
 scalar_t__ be_get_dataset_snapshots (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ be_prop_list_alloc (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  print_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct printc*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
print_snapshots(const char *dsname, struct printc *pc)
{
	nvpair_t *cur;
	nvlist_t *props, *sprops;

	if (be_prop_list_alloc(&props) != 0) {
		fprintf(stderr, "bectl list: failed to allocate snapshot nvlist\n");
		return (1);
	}
	if (be_get_dataset_snapshots(be, dsname, props) != 0) {
		fprintf(stderr, "bectl list: failed to fetch boot ds snapshots\n");
		return (1);
	}
	for (cur = nvlist_next_nvpair(props, NULL); cur != NULL;
	    cur = nvlist_next_nvpair(props, cur)) {
		nvpair_value_nvlist(cur, &sprops);
		print_info(nvpair_name(cur), sprops, pc);
	}
	return (0);
}