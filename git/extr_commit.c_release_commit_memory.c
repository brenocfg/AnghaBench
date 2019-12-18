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
struct parsed_object_pool {int dummy; } ;
struct TYPE_2__ {scalar_t__ parsed; } ;
struct commit {TYPE_1__ object; int /*<<< orphan*/  parents; scalar_t__ index; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_commit_buffer (struct parsed_object_pool*,struct commit*) ; 
 int /*<<< orphan*/  free_commit_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_commit_tree (struct commit*,int /*<<< orphan*/ *) ; 

void release_commit_memory(struct parsed_object_pool *pool, struct commit *c)
{
	set_commit_tree(c, NULL);
	free_commit_buffer(pool, c);
	c->index = 0;
	free_commit_list(c->parents);

	c->object.parsed = 0;
}