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
struct eh_frame_hdr_table_entry {scalar_t__ start; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_eh_frame_hdr_table_entries(const void *p1, const void *p2)
{
	const struct eh_frame_hdr_table_entry *e1 = p1;
	const struct eh_frame_hdr_table_entry *e2 = p2;

	return (e1->start > e2->start) - (e1->start < e2->start);
}