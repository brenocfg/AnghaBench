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
struct pair_pos_vs_id {int pack_int_id; } ;

/* Variables and functions */

__attribute__((used)) static int compare_pair_pos_vs_id(const void *_a, const void *_b)
{
	struct pair_pos_vs_id *a = (struct pair_pos_vs_id *)_a;
	struct pair_pos_vs_id *b = (struct pair_pos_vs_id *)_b;

	return b->pack_int_id - a->pack_int_id;
}