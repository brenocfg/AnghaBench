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
struct TYPE_4__ {TYPE_1__* descs; } ;
struct ck_rhs_map {unsigned long mask; int /*<<< orphan*/  probe_maximum; TYPE_2__ entries; scalar_t__ read_mostly; } ;
struct TYPE_3__ {int /*<<< orphan*/  probe_bound; } ;

/* Variables and functions */
 unsigned int CK_RHS_LOAD (int /*<<< orphan*/ *) ; 
 unsigned int CK_RHS_WORD_MAX ; 
 unsigned int ck_pr_load_uint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int
ck_rhs_map_bound_get(struct ck_rhs_map *m, unsigned long h)
{
	unsigned long offset = h & m->mask;
	unsigned int r = CK_RHS_WORD_MAX;

	if (m->read_mostly)
		r = ck_pr_load_uint(&m->probe_maximum);
	else {
		r = CK_RHS_LOAD(&m->entries.descs[offset].probe_bound);
		if (r == CK_RHS_WORD_MAX)
			r = ck_pr_load_uint(&m->probe_maximum);
	}
	return r;
}