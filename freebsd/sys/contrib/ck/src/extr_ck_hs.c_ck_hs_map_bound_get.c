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
struct ck_hs_map {unsigned long mask; int /*<<< orphan*/  probe_maximum; int /*<<< orphan*/ * probe_bound; } ;

/* Variables and functions */
 unsigned int CK_HS_LOAD (int /*<<< orphan*/ *) ; 
 unsigned int CK_HS_WORD_MAX ; 
 unsigned int ck_pr_load_uint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int
ck_hs_map_bound_get(struct ck_hs_map *m, unsigned long h)
{
	unsigned long offset = h & m->mask;
	unsigned int r = CK_HS_WORD_MAX;

	if (m->probe_bound != NULL) {
		r = CK_HS_LOAD(&m->probe_bound[offset]);
		if (r == CK_HS_WORD_MAX)
			r = ck_pr_load_uint(&m->probe_maximum);
	} else {
		r = ck_pr_load_uint(&m->probe_maximum);
	}

	return r;
}