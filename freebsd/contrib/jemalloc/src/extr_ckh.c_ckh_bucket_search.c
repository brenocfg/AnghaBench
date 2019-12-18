#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ ckhc_t ;
struct TYPE_5__ {scalar_t__ (* keycomp ) (void const*,int /*<<< orphan*/ *) ;TYPE_1__* tab; } ;
typedef  TYPE_2__ ckh_t ;

/* Variables and functions */
 unsigned int LG_CKH_BUCKET_CELLS ; 
 size_t SIZE_T_MAX ; 
 unsigned int ZU (int) ; 
 scalar_t__ stub1 (void const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
ckh_bucket_search(ckh_t *ckh, size_t bucket, const void *key) {
	ckhc_t *cell;
	unsigned i;

	for (i = 0; i < (ZU(1) << LG_CKH_BUCKET_CELLS); i++) {
		cell = &ckh->tab[(bucket << LG_CKH_BUCKET_CELLS) + i];
		if (cell->key != NULL && ckh->keycomp(key, cell->key)) {
			return (bucket << LG_CKH_BUCKET_CELLS) + i;
		}
	}

	return SIZE_T_MAX;
}