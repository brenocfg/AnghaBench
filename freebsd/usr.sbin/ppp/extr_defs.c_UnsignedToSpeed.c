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
struct speeds {unsigned int nspeed; int /*<<< orphan*/  speed; } ;
typedef  int /*<<< orphan*/  speed_t ;

/* Variables and functions */
 int /*<<< orphan*/  B0 ; 
 struct speeds* speeds ; 

speed_t
UnsignedToSpeed(unsigned nspeed)
{
  const struct speeds *sp;

  for (sp = speeds; sp->nspeed; sp++) {
    if (sp->nspeed == nspeed) {
      return sp->speed;
    }
  }
  return B0;
}