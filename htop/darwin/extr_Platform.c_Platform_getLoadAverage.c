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
 int getloadavg (double*,int) ; 

void Platform_getLoadAverage(double* one, double* five, double* fifteen) {
   double results[3];

   if(3 == getloadavg(results, 3)) {
      *one = results[0];
      *five = results[1];
      *fifteen = results[2];
   } else {
      *one = 0;
      *five = 0;
      *fifteen = 0;
   }
}