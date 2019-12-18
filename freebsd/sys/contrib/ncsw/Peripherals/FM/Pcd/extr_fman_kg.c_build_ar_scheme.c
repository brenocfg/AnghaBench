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
 int FM_KG_KGAR_SCM_WSEL_UPDATE_CNT ; 
 int FM_KG_KGAR_SEL_SCHEME_ENTRY ; 
 scalar_t__ FM_KG_KGAR_WRITE ; 

__attribute__((used)) static uint32_t build_ar_scheme(uint8_t scheme,
				uint8_t hwport_id,
				bool update_counter,
				bool write)
{
	uint32_t rw;

	rw = (uint32_t)(write ? FM_KG_KGAR_WRITE : FM_KG_KGAR_READ);

	return (uint32_t)(FM_KG_KGAR_GO |
			rw |
			FM_KG_KGAR_SEL_SCHEME_ENTRY |
			hwport_id |
			((uint32_t)scheme << FM_KG_KGAR_NUM_SHIFT) |
			(update_counter ? FM_KG_KGAR_SCM_WSEL_UPDATE_CNT : 0));
}