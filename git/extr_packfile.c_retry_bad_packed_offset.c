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
struct revindex_entry {int /*<<< orphan*/  nr; } ;
struct repository {int dummy; } ;
struct packed_git {int dummy; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int OBJ_BAD ; 
 int OBJ_NONE ; 
 struct revindex_entry* find_pack_revindex (struct packed_git*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_bad_packed_object (struct packed_git*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nth_packed_object_oid (struct object_id*,struct packed_git*,int /*<<< orphan*/ ) ; 
 int oid_object_info (struct repository*,struct object_id*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int retry_bad_packed_offset(struct repository *r,
				   struct packed_git *p,
				   off_t obj_offset)
{
	int type;
	struct revindex_entry *revidx;
	struct object_id oid;
	revidx = find_pack_revindex(p, obj_offset);
	if (!revidx)
		return OBJ_BAD;
	nth_packed_object_oid(&oid, p, revidx->nr);
	mark_bad_packed_object(p, oid.hash);
	type = oid_object_info(r, &oid, NULL);
	if (type <= OBJ_NONE)
		return OBJ_BAD;
	return type;
}