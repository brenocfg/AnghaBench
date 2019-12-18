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
struct ofs_delta_entry {scalar_t__ offset; } ;

/* Variables and functions */

__attribute__((used)) static int compare_ofs_delta_entry(const void *a, const void *b)
{
	const struct ofs_delta_entry *delta_a = a;
	const struct ofs_delta_entry *delta_b = b;

	return delta_a->offset < delta_b->offset ? -1 :
	       delta_a->offset > delta_b->offset ?  1 :
	       0;
}