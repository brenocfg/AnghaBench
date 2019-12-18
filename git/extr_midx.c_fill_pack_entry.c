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
struct pack_midx_entry {int /*<<< orphan*/  offset; int /*<<< orphan*/  pack_mtime; int /*<<< orphan*/  pack_int_id; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nth_packed_object_offset (struct packed_git*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nth_packed_object_oid (int /*<<< orphan*/ *,struct packed_git*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_pack_entry(uint32_t pack_int_id,
			    struct packed_git *p,
			    uint32_t cur_object,
			    struct pack_midx_entry *entry)
{
	if (!nth_packed_object_oid(&entry->oid, p, cur_object))
		die(_("failed to locate object %d in packfile"), cur_object);

	entry->pack_int_id = pack_int_id;
	entry->pack_mtime = p->mtime;

	entry->offset = nth_packed_object_offset(p, cur_object);
}