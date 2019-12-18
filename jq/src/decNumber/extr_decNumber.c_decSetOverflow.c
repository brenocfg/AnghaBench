#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
typedef  int uByte ;
struct TYPE_9__ {int bits; int exponent; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_10__ {int emax; int digits; int round; scalar_t__ clamp; } ;
typedef  TYPE_2__ decContext ;
typedef  int Int ;
typedef  int Flag ;

/* Variables and functions */
 int DECINF ; 
 int DECNEG ; 
 int DEC_Clamped ; 
 int DEC_Inexact ; 
 int DEC_Overflow ; 
#define  DEC_ROUND_05UP 131 
#define  DEC_ROUND_CEILING 130 
#define  DEC_ROUND_DOWN 129 
#define  DEC_ROUND_FLOOR 128 
 int DEC_Rounded ; 
 scalar_t__ ISZERO (TYPE_1__*) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 
 int /*<<< orphan*/  decSetMaxValue (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void decSetOverflow(decNumber *dn, decContext *set, uInt *status) {
  Flag needmax=0;                  // result is maximum finite value
  uByte sign=dn->bits&DECNEG;      // clean and save sign bit

  if (ISZERO(dn)) {                // zero does not overflow magnitude
    Int emax=set->emax;                      // limit value
    if (set->clamp) emax-=set->digits-1;     // lower if clamping
    if (dn->exponent>emax) {                 // clamp required
      dn->exponent=emax;
      *status|=DEC_Clamped;
      }
    return;
    }

  decNumberZero(dn);
  switch (set->round) {
    case DEC_ROUND_DOWN: {
      needmax=1;                   // never Infinity
      break;} // r-d
    case DEC_ROUND_05UP: {
      needmax=1;                   // never Infinity
      break;} // r-05
    case DEC_ROUND_CEILING: {
      if (sign) needmax=1;         // Infinity if non-negative
      break;} // r-c
    case DEC_ROUND_FLOOR: {
      if (!sign) needmax=1;        // Infinity if negative
      break;} // r-f
    default: break;                // Infinity in all other cases
    }
  if (needmax) {
    decSetMaxValue(dn, set);
    dn->bits=sign;                 // set sign
    }
   else dn->bits=sign|DECINF;      // Value is +/-Infinity
  *status|=DEC_Overflow | DEC_Inexact | DEC_Rounded;
  }