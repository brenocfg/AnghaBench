#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t digits; size_t exponent; scalar_t__ bits; scalar_t__* lsu; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_6__ {size_t digits; size_t emax; } ;
typedef  TYPE_2__ decContext ;
typedef  scalar_t__ Unit ;
typedef  size_t Int ;

/* Variables and functions */
 size_t DECDPUN ; 
 scalar_t__ DECDPUNMAX ; 
 int* powers ; 

__attribute__((used)) static void decSetMaxValue(decNumber *dn, decContext *set) {
  Unit *up;                        // work
  Int count=set->digits;           // nines to add
  dn->digits=count;
  // fill in all nines to set maximum value
  for (up=dn->lsu; ; up++) {
    if (count>DECDPUN) *up=DECDPUNMAX;  // unit full o'nines
     else {                             // this is the msu
      *up=(Unit)(powers[count]-1);
      break;
      }
    count-=DECDPUN;                // filled those digits
    } // up
  dn->bits=0;                      // + sign
  dn->exponent=set->emax-set->digits+1;
  }