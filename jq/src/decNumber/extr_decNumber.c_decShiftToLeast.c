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
typedef  int Unit ;
typedef  int Int ;

/* Variables and functions */
 int D2U (int) ; 
 int DECDPUN ; 
 int MSUDIGITS (int) ; 
 int QUOT10 (int,int) ; 
 int* powers ; 

__attribute__((used)) static Int decShiftToLeast(Unit *uar, Int units, Int shift) {
  Unit  *target, *up;              // work
  Int   cut, count;                // work
  Int   quot, rem;                 // for division

  if (shift==0) return units;      // [fastpath] nothing to do
  if (shift==units*DECDPUN) {      // [fastpath] little to do
    *uar=0;                        // all digits cleared gives zero
    return 1;                      // leaves just the one
    }

  target=uar;                      // both paths
  cut=MSUDIGITS(shift);
  if (cut==DECDPUN) {              // unit-boundary case; easy
    up=uar+D2U(shift);
    for (; up<uar+units; target++, up++) *target=*up;
    return target-uar;
    }

  // messier
  up=uar+D2U(shift-cut);           // source; correct to whole Units
  count=units*DECDPUN-shift;       // the maximum new length
  #if DECDPUN<=4
    quot=QUOT10(*up, cut);
  #else
    quot=*up/powers[cut];
  #endif
  for (; ; target++) {
    *target=(Unit)quot;
    count-=(DECDPUN-cut);
    if (count<=0) break;
    up++;
    quot=*up;
    #if DECDPUN<=4
      quot=QUOT10(quot, cut);
      rem=*up-quot*powers[cut];
    #else
      rem=quot%powers[cut];
      quot=quot/powers[cut];
    #endif
    *target=(Unit)(*target+rem*powers[DECDPUN-cut]);
    count-=cut;
    if (count<=0) break;
    }
  return target-uar+1;
  }