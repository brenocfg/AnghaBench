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
struct ib_gid_table {struct ib_gid_table* data_vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ib_gid_table*) ; 

__attribute__((used)) static void release_gid_table(struct ib_gid_table *table)
{
	if (table) {
		kfree(table->data_vec);
		kfree(table);
	}
}