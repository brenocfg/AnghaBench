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
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {scalar_t__* u16; } ;
typedef  TYPE_1__ ddt_key_cmp_t ;
struct TYPE_4__ {int /*<<< orphan*/  dde_key; } ;
typedef  TYPE_2__ ddt_entry_t ;

/* Variables and functions */
 int AVL_ISIGN (scalar_t__) ; 
 int DDT_KEY_CMP_LEN ; 
 scalar_t__ likely (scalar_t__) ; 

int
ddt_entry_compare(const void *x1, const void *x2)
{
	const ddt_entry_t *dde1 = x1;
	const ddt_entry_t *dde2 = x2;
	const ddt_key_cmp_t *k1 = (const ddt_key_cmp_t *)&dde1->dde_key;
	const ddt_key_cmp_t *k2 = (const ddt_key_cmp_t *)&dde2->dde_key;
	int32_t cmp = 0;

	for (int i = 0; i < DDT_KEY_CMP_LEN; i++) {
		cmp = (int32_t)k1->u16[i] - (int32_t)k2->u16[i];
		if (likely(cmp))
			break;
	}

	return (AVL_ISIGN(cmp));
}