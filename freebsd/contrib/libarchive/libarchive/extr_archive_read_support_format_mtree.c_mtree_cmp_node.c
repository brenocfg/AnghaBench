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
struct mtree_entry {int /*<<< orphan*/  name; } ;
struct archive_rb_node {int dummy; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtree_cmp_node(const struct archive_rb_node *n1,
    const struct archive_rb_node *n2)
{
	const struct mtree_entry *e1 = (const struct mtree_entry *)n1;
	const struct mtree_entry *e2 = (const struct mtree_entry *)n2;

	return (strcmp(e1->name, e2->name));
}