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
 int COMTICK ; 
 long SPEED_TOLERANCE ; 
 int divrnd (int,long) ; 

__attribute__((used)) static int
dos_baudconv (int rate)
{
  long x, err;

  if (rate <= 0)
    return -1;

#define divrnd(n, q)	(((n) * 2 / (q) + 1) / 2) /* divide and round off */
  x = divrnd (COMTICK, rate);
  if (x <= 0)
    return -1;

  err = divrnd (1000 * COMTICK, x * rate) - 1000;
  if (err < 0)
    err = -err;
  if (err > SPEED_TOLERANCE)
    return -1;
#undef divrnd
  return x;
}