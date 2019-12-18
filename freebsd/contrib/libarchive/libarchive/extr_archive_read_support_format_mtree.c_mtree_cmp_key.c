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
 int strcmp (int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static int
mtree_cmp_key(const struct archive_rb_node *n, const void *key)
{
	const struct mtree_entry *e = (const struct mtree_entry *)n;

	return (strcmp(e->name, key));
}