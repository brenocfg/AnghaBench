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
struct ck_barrier_combining_group {int /*<<< orphan*/  k; struct ck_barrier_combining_group* parent; } ;

/* Variables and functions */

__attribute__((used)) static void
ck_barrier_combining_insert(struct ck_barrier_combining_group *parent,
    struct ck_barrier_combining_group *tnode,
    struct ck_barrier_combining_group **child)
{

	*child = tnode;
	tnode->parent = parent;

	/*
	 * After inserting, we must increment the parent group's count for
	 * number of threads expected to reach it; otherwise, the
	 * barrier may end prematurely.
	 */
	parent->k++;
	return;
}