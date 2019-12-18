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
struct packed_git {int /*<<< orphan*/  mru; struct packed_git* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  packed_git_mru; struct packed_git* packed_git; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prepare_packed_git_mru(struct repository *r)
{
	struct packed_git *p;

	INIT_LIST_HEAD(&r->objects->packed_git_mru);

	for (p = r->objects->packed_git; p; p = p->next)
		list_add_tail(&p->mru, &r->objects->packed_git_mru);
}