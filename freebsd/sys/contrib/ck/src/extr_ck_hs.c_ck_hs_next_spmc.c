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
struct ck_hs_map {int dummy; } ;
struct ck_hs_iterator {struct ck_hs_map* map; } ;
struct ck_hs {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int _ck_hs_next (struct ck_hs*,struct ck_hs_map*,struct ck_hs_iterator*,void**) ; 
 struct ck_hs_map* ck_pr_load_ptr (int /*<<< orphan*/ *) ; 

bool
ck_hs_next_spmc(struct ck_hs *hs, struct ck_hs_iterator *i, void **key)
{
	struct ck_hs_map *m = i->map;
	if (m == NULL) {
		m = i->map = ck_pr_load_ptr(&hs->map);
	}
	return _ck_hs_next(hs, m, i, key);
}