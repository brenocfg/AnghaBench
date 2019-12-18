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

/* Variables and functions */
 size_t LOADAVG_15MIN ; 
 size_t LOADAVG_1MIN ; 
 size_t LOADAVG_5MIN ; 
 int /*<<< orphan*/  getloadavg (double*,int) ; 
 double* plat_loadavg ; 

void Platform_getLoadAverage(double* one, double* five, double* fifteen) {
   getloadavg( plat_loadavg, 3 );
   *one = plat_loadavg[LOADAVG_1MIN];
   *five = plat_loadavg[LOADAVG_5MIN];
   *fifteen = plat_loadavg[LOADAVG_15MIN];
}