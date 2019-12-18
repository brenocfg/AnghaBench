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
struct repository {TYPE_1__* objects; } ;
struct TYPE_2__ {scalar_t__ commit_graph; } ;

/* Variables and functions */
 scalar_t__ read_commit_graph_one (struct repository*,char const*) ; 

__attribute__((used)) static void prepare_commit_graph_one(struct repository *r, const char *obj_dir)
{

	if (r->objects->commit_graph)
		return;

	r->objects->commit_graph = read_commit_graph_one(r, obj_dir);
}