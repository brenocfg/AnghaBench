#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uInt ;
struct TYPE_25__ {int bits; scalar_t__ digits; scalar_t__ exponent; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_26__ {int digits; } ;
typedef  TYPE_2__ decContext ;
typedef  scalar_t__ Int ;

/* Variables and functions */
 int D2N (int) ; 
 int DECINF ; 
 int DECNEG ; 
 int /*<<< orphan*/  DECUNUSED ; 
 int /*<<< orphan*/  DEC_Division_by_zero ; 
 scalar_t__ decCheckOperands (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  decNaNs (TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decNumberCopyAbs (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  decNumberFromInt32 (TYPE_1__*,scalar_t__) ; 
 scalar_t__ decNumberIsInfinite (TYPE_1__ const*) ; 
 scalar_t__ decNumberIsNaN (TYPE_1__ const*) ; 
 scalar_t__ decNumberIsZero (TYPE_1__ const*) ; 
 int /*<<< orphan*/  decNumberPlus (TYPE_1__*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 
 int /*<<< orphan*/  decStatus (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 

decNumber * decNumberLogB(decNumber *res, const decNumber *rhs,
                          decContext *set) {
  uInt status=0;                   // accumulator

  #if DECCHECK
  if (decCheckOperands(res, DECUNUSED, rhs, set)) return res;
  #endif

  // NaNs as usual; Infinities return +Infinity; 0->oops
  if (decNumberIsNaN(rhs)) decNaNs(res, rhs, NULL, set, &status);
   else if (decNumberIsInfinite(rhs)) decNumberCopyAbs(res, rhs);
   else if (decNumberIsZero(rhs)) {
    decNumberZero(res);                 // prepare for Infinity
    res->bits=DECNEG|DECINF;            // -Infinity
    status|=DEC_Division_by_zero;       // as per 754
    }
   else { // finite non-zero
    Int ae=rhs->exponent+rhs->digits-1; // adjusted exponent
    if (set->digits>=10) decNumberFromInt32(res, ae);  // lay it out
     else {
      decNumber buft[D2N(10)];          // temporary number
      decNumber *t=buft;                // ..
      decNumberFromInt32(t, ae);        // lay it out
      decNumberPlus(res, t, set);       // round as necessary
      }
    }

  if (status!=0) decStatus(res, status, set);
  return res;
  }