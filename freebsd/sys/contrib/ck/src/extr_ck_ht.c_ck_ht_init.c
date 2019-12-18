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
typedef  int /*<<< orphan*/  uint64_t ;
struct ck_malloc {int /*<<< orphan*/ * free; int /*<<< orphan*/ * malloc; } ;
struct ck_ht {unsigned int mode; int /*<<< orphan*/ * map; int /*<<< orphan*/ * h; int /*<<< orphan*/  seed; struct ck_malloc* m; } ;
typedef  int /*<<< orphan*/  ck_ht_hash_cb_t ;
typedef  int /*<<< orphan*/  CK_HT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/ * ck_ht_hash_wrapper ; 
 int /*<<< orphan*/ * ck_ht_map_create (struct ck_ht*,int /*<<< orphan*/ ) ; 

bool
ck_ht_init(struct ck_ht *table,
    unsigned int mode,
    ck_ht_hash_cb_t *h,
    struct ck_malloc *m,
    CK_HT_TYPE entries,
    uint64_t seed)
{

	if (m == NULL || m->malloc == NULL || m->free == NULL)
		return false;

	table->m = m;
	table->mode = mode;
	table->seed = seed;

	if (h == NULL) {
		table->h = ck_ht_hash_wrapper;
	} else {
		table->h = h;
	}

	table->map = ck_ht_map_create(table, entries);
	return table->map != NULL;
}