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
struct ck_malloc {int /*<<< orphan*/ * free; int /*<<< orphan*/ * malloc; } ;
struct ck_hs {unsigned int mode; unsigned long seed; int /*<<< orphan*/ * map; int /*<<< orphan*/ * compare; int /*<<< orphan*/ * hf; struct ck_malloc* m; } ;
typedef  int /*<<< orphan*/  ck_hs_hash_cb_t ;
typedef  int /*<<< orphan*/  ck_hs_compare_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ck_hs_map_create (struct ck_hs*,unsigned long) ; 

bool
ck_hs_init(struct ck_hs *hs,
    unsigned int mode,
    ck_hs_hash_cb_t *hf,
    ck_hs_compare_cb_t *compare,
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

	hs->map = ck_hs_map_create(hs, n_entries);
	return hs->map != NULL;
}