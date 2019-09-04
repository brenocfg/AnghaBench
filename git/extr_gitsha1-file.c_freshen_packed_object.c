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
struct pack_entry {TYPE_1__* p; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int freshened; int /*<<< orphan*/  pack_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_pack_entry (int /*<<< orphan*/ ,struct object_id const*,struct pack_entry*) ; 
 int /*<<< orphan*/  freshen_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int freshen_packed_object(const struct object_id *oid)
{
	struct pack_entry e;
	if (!find_pack_entry(the_repository, oid, &e))
		return 0;
	if (e.p->freshened)
		return 1;
	if (!freshen_file(e.p->pack_name))
		return 0;
	e.p->freshened = 1;
	return 1;
}