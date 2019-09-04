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
struct index_state {int /*<<< orphan*/ * cache_tree; int /*<<< orphan*/ * untracked; } ;

/* Variables and functions */

void move_index_extensions(struct index_state *dst, struct index_state *src)
{
	dst->untracked = src->untracked;
	src->untracked = NULL;
	dst->cache_tree = src->cache_tree;
	src->cache_tree = NULL;
}