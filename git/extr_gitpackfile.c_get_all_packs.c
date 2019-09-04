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
typedef  size_t uint32_t ;
struct repository {TYPE_1__* objects; } ;
struct packed_git {struct packed_git* next; } ;
struct multi_pack_index {size_t num_packs; struct packed_git** packs; struct multi_pack_index* next; } ;
struct TYPE_2__ {struct packed_git* all_packs; struct multi_pack_index* multi_pack_index; struct packed_git* packed_git; } ;

/* Variables and functions */
 int /*<<< orphan*/  prepare_midx_pack (struct multi_pack_index*,size_t) ; 
 int /*<<< orphan*/  prepare_packed_git (struct repository*) ; 

struct packed_git *get_all_packs(struct repository *r)
{
	prepare_packed_git(r);

	if (!r->objects->all_packs) {
		struct packed_git *p = r->objects->packed_git;
		struct multi_pack_index *m;

		for (m = r->objects->multi_pack_index; m; m = m->next) {
			uint32_t i;
			for (i = 0; i < m->num_packs; i++) {
				if (!prepare_midx_pack(m, i)) {
					m->packs[i]->next = p;
					p = m->packs[i];
				}
			}
		}

		r->objects->all_packs = p;
	}

	return r->objects->all_packs;
}