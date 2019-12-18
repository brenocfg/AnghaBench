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
struct eh_frame_hdr_table_entry {unsigned long start; unsigned long fde; } ;

/* Variables and functions */

__attribute__((used)) static void swap_eh_frame_hdr_table_entries(void *p1, void *p2, int size)
{
	struct eh_frame_hdr_table_entry *e1 = p1;
	struct eh_frame_hdr_table_entry *e2 = p2;
	unsigned long v;

	v = e1->start;
	e1->start = e2->start;
	e2->start = v;
	v = e1->fde;
	e1->fde = e2->fde;
	e2->fde = v;
}