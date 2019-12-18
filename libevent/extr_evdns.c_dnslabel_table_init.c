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
struct dnslabel_table {scalar_t__ n_labels; } ;

/* Variables and functions */

__attribute__((used)) static void
dnslabel_table_init(struct dnslabel_table *table)
{
	table->n_labels = 0;
}