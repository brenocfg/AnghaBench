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
struct packed_git {scalar_t__ pack_keep; int /*<<< orphan*/  pack_local; struct packed_git* next; } ;

/* Variables and functions */
 int gc_auto_pack_limit ; 
 struct packed_git* get_all_packs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int too_many_packs(void)
{
	struct packed_git *p;
	int cnt;

	if (gc_auto_pack_limit <= 0)
		return 0;

	for (cnt = 0, p = get_all_packs(the_repository); p; p = p->next) {
		if (!p->pack_local)
			continue;
		if (p->pack_keep)
			continue;
		/*
		 * Perhaps check the size of the pack and count only
		 * very small ones here?
		 */
		cnt++;
	}
	return gc_auto_pack_limit < cnt;
}