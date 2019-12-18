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
struct base_tree_info {int nr_patch_id; int /*<<< orphan*/  base_commit; scalar_t__ alloc_patch_id; int /*<<< orphan*/ * patch_id; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_bases(struct base_tree_info *bases, FILE *file)
{
	int i;

	/* Only do this once, either for the cover or for the first one */
	if (is_null_oid(&bases->base_commit))
		return;

	/* Show the base commit */
	fprintf(file, "\nbase-commit: %s\n", oid_to_hex(&bases->base_commit));

	/* Show the prerequisite patches */
	for (i = bases->nr_patch_id - 1; i >= 0; i--)
		fprintf(file, "prerequisite-patch-id: %s\n", oid_to_hex(&bases->patch_id[i]));

	free(bases->patch_id);
	bases->nr_patch_id = 0;
	bases->alloc_patch_id = 0;
	oidclr(&bases->base_commit);
}