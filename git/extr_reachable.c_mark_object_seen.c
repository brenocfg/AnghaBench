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
struct packed_git {int dummy; } ;
struct object_id {int dummy; } ;
struct object {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  SEEN ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 struct object* lookup_object_by_type (int /*<<< orphan*/ ,struct object_id const*,int) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int mark_object_seen(const struct object_id *oid,
			     enum object_type type,
			     int exclude,
			     uint32_t name_hash,
			     struct packed_git *found_pack,
			     off_t found_offset)
{
	struct object *obj = lookup_object_by_type(the_repository, oid, type);
	if (!obj)
		die("unable to create object '%s'", oid_to_hex(oid));

	obj->flags |= SEEN;
	return 0;
}