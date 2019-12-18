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
struct dir_entry {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int name_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cmp_dir_entry(const void *p1, const void *p2)
{
	const struct dir_entry *e1 = *(const struct dir_entry **)p1;
	const struct dir_entry *e2 = *(const struct dir_entry **)p2;

	return name_compare(e1->name, e1->len, e2->name, e2->len);
}