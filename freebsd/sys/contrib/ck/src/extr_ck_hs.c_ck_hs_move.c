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
struct ck_hs {int /*<<< orphan*/ * compare; int /*<<< orphan*/ * hf; struct ck_malloc* m; int /*<<< orphan*/  map; int /*<<< orphan*/  seed; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  ck_hs_hash_cb_t ;
typedef  int /*<<< orphan*/  ck_hs_compare_cb_t ;

/* Variables and functions */

bool
ck_hs_move(struct ck_hs *hs,
    struct ck_hs *source,
    ck_hs_hash_cb_t *hf,
    ck_hs_compare_cb_t *compare,
    struct ck_malloc *m)
{

	if (m == NULL || m->malloc == NULL || m->free == NULL || hf == NULL)
		return false;

	hs->mode = source->mode;
	hs->seed = source->seed;
	hs->map = source->map;
	hs->m = m;
	hs->hf = hf;
	hs->compare = compare;
	return true;
}