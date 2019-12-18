#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
typedef  scalar_t__ uByte ;
struct TYPE_4__ {int digits; scalar_t__* lsu; } ;
typedef  TYPE_1__ decNumber ;
typedef  scalar_t__ Unit ;
typedef  scalar_t__ Int ;

/* Variables and functions */
 int D2U (int) ; 
 scalar_t__ DECDPUN ; 
 scalar_t__ MSUDIGITS (int) ; 
 scalar_t__ const X10 (scalar_t__) ; 

decNumber * decNumberSetBCD(decNumber *dn, const uByte *bcd, uInt n) {
  Unit *up=dn->lsu+D2U(dn->digits)-1;   // -> msu [target pointer]
  const uByte *ub=bcd;                  // -> source msd

  #if DECDPUN==1                        // trivial simple copy
    for (; ub<bcd+n; ub++, up--) *up=*ub;
  #else                                 // some assembly needed
    // calculate how many digits in msu, and hence first cut
    Int cut=MSUDIGITS(n);               // [faster than remainder]
    for (;up>=dn->lsu; up--) {          // each Unit from msu
      *up=0;                            // will take <=DECDPUN digits
      for (; cut>0; ub++, cut--) *up=X10(*up)+*ub;
      cut=DECDPUN;                      // next Unit has all digits
      }
  #endif
  dn->digits=n;                         // set digit count
  return dn;
  }