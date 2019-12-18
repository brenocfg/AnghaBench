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
struct rev_info {int /*<<< orphan*/  repo; } ;
struct packed_git {int dummy; } ;
struct object_id {int dummy; } ;
struct object {int flags; } ;

/* Variables and functions */
 int SEEN ; 
 int UNINTERESTING ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 

__attribute__((used)) static int mark_uninteresting(const struct object_id *oid,
			      struct packed_git *pack,
			      uint32_t pos,
			      void *cb)
{
	struct rev_info *revs = cb;
	struct object *o = parse_object(revs->repo, oid);
	o->flags |= UNINTERESTING | SEEN;
	return 0;
}