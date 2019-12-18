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
typedef  int uInt ;
typedef  int Unit ;
typedef  size_t Int ;

/* Variables and functions */
 int D2U (size_t) ; 
 size_t DECDPUN ; 
 size_t MSUDIGITS (size_t) ; 
 int QUOT10 (int,size_t) ; 
 int* powers ; 

__attribute__((used)) static Int decShiftToMost(Unit *uar, Int digits, Int shift) {
  Unit  *target, *source, *first;  // work
  Int   cut;                       // odd 0's to add
  uInt  next;                      // work

  if (shift==0) return digits;     // [fastpath] nothing to do
  if ((digits+shift)<=DECDPUN) {   // [fastpath] single-unit case
    *uar=(Unit)(*uar*powers[shift]);
    return digits+shift;
    }

  next=0;                          // all paths
  source=uar+D2U(digits)-1;        // where msu comes from
  target=source+D2U(shift);        // where upper part of first cut goes
  cut=DECDPUN-MSUDIGITS(shift);    // where to slice
  if (cut==0) {                    // unit-boundary case
    for (; source>=uar; source--, target--) *target=*source;
    }
   else {
    first=uar+D2U(digits+shift)-1; // where msu of source will end up
    for (; source>=uar; source--, target--) {
      // split the source Unit and accumulate remainder for next
      #if DECDPUN<=4
        uInt quot=QUOT10(*source, cut);
        uInt rem=*source-quot*powers[cut];
        next+=quot;
      #else
        uInt rem=*source%powers[cut];
        next+=*source/powers[cut];
      #endif
      if (target<=first) *target=(Unit)next;   // write to target iff valid
      next=rem*powers[DECDPUN-cut];            // save remainder for next Unit
      }
    } // shift-move

  // propagate any partial unit to one below and clear the rest
  for (; target>=uar; target--) {
    *target=(Unit)next;
    next=0;
    }
  return digits+shift;
  }