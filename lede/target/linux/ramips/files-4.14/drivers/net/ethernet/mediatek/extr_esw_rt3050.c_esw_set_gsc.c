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
struct rt305x_esw {int bc_storm_protect; int led_frequency; } ;

/* Variables and functions */
 int RT305X_ESW_GSC_BC_STROM_MASK ; 
 int RT305X_ESW_GSC_BC_STROM_SHIFT ; 
 int RT305X_ESW_GSC_LED_FREQ_MASK ; 
 int RT305X_ESW_GSC_LED_FREQ_SHIFT ; 
 int /*<<< orphan*/  RT305X_ESW_REG_SGC ; 
 int /*<<< orphan*/  esw_rmw (struct rt305x_esw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void esw_set_gsc(struct rt305x_esw *esw)
{
	esw_rmw(esw, RT305X_ESW_REG_SGC,
		RT305X_ESW_GSC_BC_STROM_MASK << RT305X_ESW_GSC_BC_STROM_SHIFT,
		esw->bc_storm_protect << RT305X_ESW_GSC_BC_STROM_SHIFT);
	esw_rmw(esw, RT305X_ESW_REG_SGC,
		RT305X_ESW_GSC_LED_FREQ_MASK << RT305X_ESW_GSC_LED_FREQ_SHIFT,
		esw->led_frequency << RT305X_ESW_GSC_LED_FREQ_SHIFT);
}