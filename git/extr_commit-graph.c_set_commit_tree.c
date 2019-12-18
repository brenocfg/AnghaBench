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
struct tree {int dummy; } ;
struct commit {struct tree* maybe_tree; } ;

/* Variables and functions */

__attribute__((used)) static inline void set_commit_tree(struct commit *c, struct tree *t)
{
	c->maybe_tree = t;
}