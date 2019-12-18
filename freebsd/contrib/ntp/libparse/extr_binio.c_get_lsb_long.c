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
typedef  int u_long ;

/* Variables and functions */

long
get_lsb_long(
	unsigned char **bufpp
	)
{
  long retval;

  retval  = *((*bufpp)++);
  retval |= *((*bufpp)++) << 8;
  retval |= *((*bufpp)++) << 16;
  retval |= (u_long)*((*bufpp)++) << 24;

  return retval;
}