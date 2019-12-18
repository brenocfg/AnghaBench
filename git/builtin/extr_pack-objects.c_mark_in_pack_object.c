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
struct packed_git {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct object {TYPE_1__ oid; } ;
struct in_pack {size_t nr; TYPE_2__* array; } ;
struct TYPE_4__ {struct object* object; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_pack_entry_one (int /*<<< orphan*/ ,struct packed_git*) ; 

__attribute__((used)) static void mark_in_pack_object(struct object *object, struct packed_git *p, struct in_pack *in_pack)
{
	in_pack->array[in_pack->nr].offset = find_pack_entry_one(object->oid.hash, p);
	in_pack->array[in_pack->nr].object = object;
	in_pack->nr++;
}