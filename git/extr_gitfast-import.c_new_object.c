#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct object_entry {TYPE_1__ idx; } ;
struct TYPE_4__ {scalar_t__ next_free; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_objects (int /*<<< orphan*/ ) ; 
 TYPE_2__* blocks ; 
 int /*<<< orphan*/  object_entry_alloc ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 

__attribute__((used)) static struct object_entry *new_object(struct object_id *oid)
{
	struct object_entry *e;

	if (blocks->next_free == blocks->end)
		alloc_objects(object_entry_alloc);

	e = blocks->next_free++;
	oidcpy(&e->idx.oid, oid);
	return e;
}