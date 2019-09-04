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
struct pack_list {struct pack_list* next; int /*<<< orphan*/  pack; } ;

/* Variables and functions */
 scalar_t__ sizeof_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t get_pack_redundancy(struct pack_list *pl)
{
	struct pack_list *subset;
	size_t ret = 0;

	if (pl == NULL)
		return 0;

	while ((subset = pl->next)) {
		while (subset) {
			ret += sizeof_union(pl->pack, subset->pack);
			subset = subset->next;
		}
		pl = pl->next;
	}
	return ret;
}