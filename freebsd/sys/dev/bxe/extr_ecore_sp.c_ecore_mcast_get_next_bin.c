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
struct TYPE_3__ {scalar_t__* vec; } ;
struct TYPE_4__ {TYPE_1__ aprox_match; } ;
struct ecore_mcast_obj {TYPE_2__ registry; } ;

/* Variables and functions */
 int BIT_VEC64_ELEM_SZ ; 
 scalar_t__ BIT_VEC64_TEST_BIT (scalar_t__*,int) ; 
 int ECORE_MCAST_VEC_SZ ; 

__attribute__((used)) static inline int ecore_mcast_get_next_bin(struct ecore_mcast_obj *o, int last)
{
	int i, j, inner_start = last % BIT_VEC64_ELEM_SZ;

	for (i = last / BIT_VEC64_ELEM_SZ; i < ECORE_MCAST_VEC_SZ; i++) {
		if (o->registry.aprox_match.vec[i])
			for (j = inner_start; j < BIT_VEC64_ELEM_SZ; j++) {
				int cur_bit = j + BIT_VEC64_ELEM_SZ * i;
				if (BIT_VEC64_TEST_BIT(o->registry.aprox_match.
						       vec, cur_bit)) {
					return cur_bit;
				}
			}
		inner_start = 0;
	}

	/* None found */
	return -1;
}