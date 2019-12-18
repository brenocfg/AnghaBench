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
struct remote {int /*<<< orphan*/  name; } ;
struct known_remotes {struct known_remote* list; TYPE_1__* to_delete; } ;
struct known_remote {struct known_remote* next; struct remote* remote; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct known_remote* xmalloc (int) ; 

__attribute__((used)) static int add_known_remote(struct remote *remote, void *cb_data)
{
	struct known_remotes *all = cb_data;
	struct known_remote *r;

	if (!strcmp(all->to_delete->name, remote->name))
		return 0;

	r = xmalloc(sizeof(*r));
	r->remote = remote;
	r->next = all->list;
	all->list = r;
	return 0;
}