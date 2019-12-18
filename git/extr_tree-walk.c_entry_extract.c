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
struct name_entry {int dummy; } ;
struct tree_desc {struct name_entry entry; } ;

/* Variables and functions */

__attribute__((used)) static void entry_extract(struct tree_desc *t, struct name_entry *a)
{
	*a = t->entry;
}