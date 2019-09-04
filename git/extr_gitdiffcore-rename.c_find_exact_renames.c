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
struct hashmap {int dummy; } ;
struct diff_options {int /*<<< orphan*/  repo; } ;
struct TYPE_4__ {TYPE_1__* p; } ;
struct TYPE_3__ {int /*<<< orphan*/  one; } ;

/* Variables and functions */
 scalar_t__ find_identical_files (struct hashmap*,int,struct diff_options*) ; 
 int /*<<< orphan*/  hashmap_free (struct hashmap*,int) ; 
 int /*<<< orphan*/  hashmap_init (struct hashmap*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  insert_file_table (int /*<<< orphan*/ ,struct hashmap*,int,int /*<<< orphan*/ ) ; 
 int rename_dst_nr ; 
 TYPE_2__* rename_src ; 
 int rename_src_nr ; 

__attribute__((used)) static int find_exact_renames(struct diff_options *options)
{
	int i, renames = 0;
	struct hashmap file_table;

	/* Add all sources to the hash table in reverse order, because
	 * later on they will be retrieved in LIFO order.
	 */
	hashmap_init(&file_table, NULL, NULL, rename_src_nr);
	for (i = rename_src_nr-1; i >= 0; i--)
		insert_file_table(options->repo,
				  &file_table, i,
				  rename_src[i].p->one);

	/* Walk the destinations and find best source match */
	for (i = 0; i < rename_dst_nr; i++)
		renames += find_identical_files(&file_table, i, options);

	/* Free the hash data structure and entries */
	hashmap_free(&file_table, 1);

	return renames;
}