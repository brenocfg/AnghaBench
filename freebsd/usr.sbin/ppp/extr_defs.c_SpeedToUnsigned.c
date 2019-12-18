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
struct speeds {int nspeed; scalar_t__ speed; } ;
typedef  scalar_t__ speed_t ;

/* Variables and functions */
 struct speeds* speeds ; 

unsigned
SpeedToUnsigned(speed_t speed)
{
  const struct speeds *sp;

  for (sp = speeds; sp->nspeed; sp++) {
    if (sp->speed == speed) {
      return sp->nspeed;
    }
  }
  return 0;
}