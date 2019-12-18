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
struct TYPE_5__ {size_t lg_curbuckets; TYPE_1__* tab; } ;
typedef  TYPE_2__ ckh_t ;
struct TYPE_4__ {scalar_t__ data; int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 size_t LG_CKH_BUCKET_CELLS ; 
 size_t ZU (int) ; 

bool
ckh_iter(ckh_t *ckh, size_t *tabind, void **key, void **data) {
	size_t i, ncells;

	for (i = *tabind, ncells = (ZU(1) << (ckh->lg_curbuckets +
	    LG_CKH_BUCKET_CELLS)); i < ncells; i++) {
		if (ckh->tab[i].key != NULL) {
			if (key != NULL) {
				*key = (void *)ckh->tab[i].key;
			}
			if (data != NULL) {
				*data = (void *)ckh->tab[i].data;
			}
			*tabind = i + 1;
			return false;
		}
	}

	return true;
}