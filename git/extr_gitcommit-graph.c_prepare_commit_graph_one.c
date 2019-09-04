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
struct TYPE_2__ {int /*<<< orphan*/  commit_graph; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (char*) ; 
 char* get_commit_graph_filename (char const*) ; 
 int /*<<< orphan*/  load_commit_graph_one (char*) ; 

__attribute__((used)) static void prepare_commit_graph_one(struct repository *r, const char *obj_dir)
{
	char *graph_name;

	if (r->objects->commit_graph)
		return;

	graph_name = get_commit_graph_filename(obj_dir);
	r->objects->commit_graph =
		load_commit_graph_one(graph_name);

	FREE_AND_NULL(graph_name);
}