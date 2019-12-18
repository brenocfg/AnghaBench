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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int FM_KG_KGAR_GO ; 
 int FM_KG_KGAR_NUM_SHIFT ; 
 scalar_t__ FM_KG_KGAR_READ ; 
 scalar_t__ FM_KG_KGAR_WRITE ; 
 int FM_KG_KGAR_WSEL_SHIFT ; 
 int FM_PCD_KG_KGAR_SEL_CLS_PLAN_ENTRY ; 

__attribute__((used)) static uint32_t build_ar_cls_plan(uint8_t grp,
					uint8_t entries_mask,
					uint8_t hwport_id,
					bool write)
{
	uint32_t rw;

	rw = (uint32_t)(write ? FM_KG_KGAR_WRITE : FM_KG_KGAR_READ);

	return (uint32_t)(FM_KG_KGAR_GO |
			rw |
			FM_PCD_KG_KGAR_SEL_CLS_PLAN_ENTRY |
			hwport_id |
			((uint32_t)grp << FM_KG_KGAR_NUM_SHIFT) |
			((uint32_t)entries_mask << FM_KG_KGAR_WSEL_SHIFT));
}