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
struct zip_entry {scalar_t__ local_header_offset; } ;
struct archive_rb_node {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
cmp_node(const struct archive_rb_node *n1, const struct archive_rb_node *n2)
{
	const struct zip_entry *e1 = (const struct zip_entry *)n1;
	const struct zip_entry *e2 = (const struct zip_entry *)n2;

	if (e1->local_header_offset > e2->local_header_offset)
		return -1;
	if (e1->local_header_offset < e2->local_header_offset)
		return 1;
	return 0;
}