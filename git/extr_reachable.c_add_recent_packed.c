#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct packed_git {int /*<<< orphan*/  mtime; } ;
struct object_id {int dummy; } ;
struct object {int flags; } ;

/* Variables and functions */
 int SEEN ; 
 int /*<<< orphan*/  add_recent_object (struct object_id const*,int /*<<< orphan*/ ,void*) ; 
 struct object* lookup_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int add_recent_packed(const struct object_id *oid,
			     struct packed_git *p, uint32_t pos,
			     void *data)
{
	struct object *obj = lookup_object(the_repository, oid);

	if (obj && obj->flags & SEEN)
		return 0;
	add_recent_object(oid, p->mtime, data);
	return 0;
}