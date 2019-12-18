#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int* vl_by_sl_num; } ;
typedef  TYPE_1__ ib_slvl_table_t ;

/* Variables and functions */

__attribute__((used)) static inline void ib_slvl_get_i(ib_slvl_table_t * tbl, int i, uint8_t * vl)
{
	*vl = (tbl->vl_by_sl_num[i >> 1] >> ((!(i & 1)) << 2)) & 0xf;
}