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
struct string_list {int nr; TYPE_1__* items; } ;
struct packed_git {int pack_keep_in_core; int /*<<< orphan*/  pack_local; int /*<<< orphan*/  pack_name; struct packed_git* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 char* basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fspathcmp (char const*,int /*<<< orphan*/ ) ; 
 struct packed_git* get_all_packs (int /*<<< orphan*/ ) ; 
 int ignore_packed_keep_in_core ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void add_extra_kept_packs(const struct string_list *names)
{
	struct packed_git *p;

	if (!names->nr)
		return;

	for (p = get_all_packs(the_repository); p; p = p->next) {
		const char *name = basename(p->pack_name);
		int i;

		if (!p->pack_local)
			continue;

		for (i = 0; i < names->nr; i++)
			if (!fspathcmp(name, names->items[i].string))
				break;

		if (i < names->nr) {
			p->pack_keep_in_core = 1;
			ignore_packed_keep_in_core = 1;
			continue;
		}
	}
}