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
struct ck_rhs {unsigned int mode; unsigned long seed; int /*<<< orphan*/ * map; int /*<<< orphan*/  load_factor; int /*<<< orphan*/ * compare; int /*<<< orphan*/ * hf; struct ck_malloc* m; } ;
struct ck_malloc {int /*<<< orphan*/ * free; int /*<<< orphan*/ * malloc; } ;
typedef  int /*<<< orphan*/  ck_rhs_hash_cb_t ;
typedef  int /*<<< orphan*/  ck_rhs_compare_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  CK_RHS_DEFAULT_LOAD_FACTOR ; 
 int /*<<< orphan*/ * ck_rhs_map_create (struct ck_rhs*,unsigned long) ; 

bool
ck_rhs_init(struct ck_rhs *hs,
    unsigned int mode,
    ck_rhs_hash_cb_t *hf,
    ck_rhs_compare_cb_t *compare,
    struct ck_malloc *m,
    unsigned long n_entries,
    unsigned long seed)
{

	if (m == NULL || m->malloc == NULL || m->free == NULL || hf == NULL)
		return false;

	hs->m = m;
	hs->mode = mode;
	hs->seed = seed;
	hs->hf = hf;
	hs->compare = compare;
	hs->load_factor = CK_RHS_DEFAULT_LOAD_FACTOR;

	hs->map = ck_rhs_map_create(hs, n_entries);
	return hs->map != NULL;
}