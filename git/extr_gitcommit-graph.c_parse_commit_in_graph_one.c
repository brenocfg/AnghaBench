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
struct repository {int dummy; } ;
struct commit_graph {int dummy; } ;
struct TYPE_2__ {scalar_t__ parsed; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int fill_commit_in_graph (struct repository*,struct commit*,struct commit_graph*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_commit_in_graph (struct commit*,struct commit_graph*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_commit_in_graph_one(struct repository *r,
				     struct commit_graph *g,
				     struct commit *item)
{
	uint32_t pos;

	if (item->object.parsed)
		return 1;

	if (find_commit_in_graph(item, g, &pos))
		return fill_commit_in_graph(r, item, g, pos);

	return 0;
}