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
struct ref_delta_entry {int obj_no; } ;

/* Variables and functions */

__attribute__((used)) static int delta_pos_compare(const void *_a, const void *_b)
{
	struct ref_delta_entry *a = *(struct ref_delta_entry **)_a;
	struct ref_delta_entry *b = *(struct ref_delta_entry **)_b;
	return a->obj_no - b->obj_no;
}