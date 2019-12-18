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
 scalar_t__ FM_KG_KGAR_READ ; 
 scalar_t__ FM_KG_KGAR_WRITE ; 
 int FM_PCD_KG_KGAR_SEL_PORT_ENTRY ; 
 int FM_PCD_KG_KGAR_SEL_PORT_WSEL_SP ; 

__attribute__((used)) static uint32_t build_ar_bind_scheme(uint8_t hwport_id, bool write)
{
	uint32_t rw;

	rw = write ? (uint32_t)FM_KG_KGAR_WRITE : (uint32_t)FM_KG_KGAR_READ;

	return (uint32_t)(FM_KG_KGAR_GO |
			rw |
			FM_PCD_KG_KGAR_SEL_PORT_ENTRY |
			hwport_id |
			FM_PCD_KG_KGAR_SEL_PORT_WSEL_SP);
}