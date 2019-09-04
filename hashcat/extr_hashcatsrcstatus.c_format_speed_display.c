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
typedef  size_t u32 ;

/* Variables and functions */
 int* UNITS ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,double,...) ; 

void format_speed_display (double val, char *buf, size_t len)
{
  if (val <= 0)
  {
    buf[0] = '0';
    buf[1] = ' ';
    buf[2] = 0;

    return;
  }

  u32 level = 0;

  while (val > 99999)
  {
    val /= 1000;

    level++;
  }

  /* generate output */

  if (level == 0)
  {
    snprintf (buf, len, "%.0f ", val);
  }
  else
  {
    snprintf (buf, len, "%.1f %c", val, UNITS[level]);
  }
}