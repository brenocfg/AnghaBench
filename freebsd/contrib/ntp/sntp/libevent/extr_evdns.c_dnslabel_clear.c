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
struct dnslabel_table {int n_labels; TYPE_1__* labels; } ;
struct TYPE_2__ {int /*<<< orphan*/  v; } ;

/* Variables and functions */
 int /*<<< orphan*/  mm_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dnslabel_clear(struct dnslabel_table *table)
{
	int i;
	for (i = 0; i < table->n_labels; ++i)
		mm_free(table->labels[i].v);
	table->n_labels = 0;
}