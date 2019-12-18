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
struct TYPE_2__ {int /*<<< orphan*/  sodest; int /*<<< orphan*/  date; int /*<<< orphan*/  name; int /*<<< orphan*/  title; int /*<<< orphan*/  arch; int /*<<< orphan*/  os; int /*<<< orphan*/  vol; int /*<<< orphan*/  msec; int /*<<< orphan*/ * first; } ;
struct roff_man {TYPE_1__ meta; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roff_node_delete (struct roff_man*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
roff_man_free1(struct roff_man *man)
{
	if (man->meta.first != NULL)
		roff_node_delete(man, man->meta.first);
	free(man->meta.msec);
	free(man->meta.vol);
	free(man->meta.os);
	free(man->meta.arch);
	free(man->meta.title);
	free(man->meta.name);
	free(man->meta.date);
	free(man->meta.sodest);
}