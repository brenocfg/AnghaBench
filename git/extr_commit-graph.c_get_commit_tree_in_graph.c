#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tree {int dummy; } ;
struct repository {TYPE_1__* objects; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit_graph; } ;

/* Variables and functions */
 struct tree* get_commit_tree_in_graph_one (struct repository*,int /*<<< orphan*/ ,struct commit const*) ; 

struct tree *get_commit_tree_in_graph(struct repository *r, const struct commit *c)
{
	return get_commit_tree_in_graph_one(r, r->objects->commit_graph, c);
}