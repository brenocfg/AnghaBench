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
 int sourcedesc ; 
 scalar_t__ sourceptr ; 

close (int desc)
{
  sourceptr = 0;
  sourcedesc++;
  /* Don't let sourcedesc get big enough to be confused with stdin.  */
  if (sourcedesc == 100)
    sourcedesc = 5;
}