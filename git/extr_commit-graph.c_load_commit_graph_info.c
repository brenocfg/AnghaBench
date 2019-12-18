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
typedef  int /*<<< orphan*/  uint32_t ;
struct repository {TYPE_1__* objects; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit_graph; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill_commit_graph_info (struct commit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_commit_in_graph (struct commit*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_commit_graph (struct repository*) ; 

void load_commit_graph_info(struct repository *r, struct commit *item)
{
	uint32_t pos;
	if (!prepare_commit_graph(r))
		return;
	if (find_commit_in_graph(item, r->objects->commit_graph, &pos))
		fill_commit_graph_info(item, r->objects->commit_graph, pos);
}