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
typedef  scalar_t__ uint32_t ;
struct repository {TYPE_1__* objects; } ;
struct packed_git {int dummy; } ;
struct multi_pack_index {scalar_t__ num_packs; struct multi_pack_index* next; } ;
struct TYPE_2__ {struct packed_git* packed_git; struct multi_pack_index* multi_pack_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  prepare_midx_pack (struct repository*,struct multi_pack_index*,scalar_t__) ; 
 int /*<<< orphan*/  prepare_packed_git (struct repository*) ; 

struct packed_git *get_all_packs(struct repository *r)
{
	struct multi_pack_index *m;

	prepare_packed_git(r);
	for (m = r->objects->multi_pack_index; m; m = m->next) {
		uint32_t i;
		for (i = 0; i < m->num_packs; i++)
			prepare_midx_pack(r, m, i);
	}

	return r->objects->packed_git;
}