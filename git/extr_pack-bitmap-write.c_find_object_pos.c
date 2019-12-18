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
typedef  int /*<<< orphan*/  uint32_t ;
struct object_id {int dummy; } ;
struct object_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  to_pack; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oe_in_pack_pos (int /*<<< orphan*/ ,struct object_entry*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 struct object_entry* packlist_find (int /*<<< orphan*/ ,struct object_id const*) ; 
 TYPE_1__ writer ; 

__attribute__((used)) static uint32_t find_object_pos(const struct object_id *oid)
{
	struct object_entry *entry = packlist_find(writer.to_pack, oid);

	if (!entry) {
		die("Failed to write bitmap index. Packfile doesn't have full closure "
			"(object %s is missing)", oid_to_hex(oid));
	}

	return oe_in_pack_pos(writer.to_pack, entry);
}