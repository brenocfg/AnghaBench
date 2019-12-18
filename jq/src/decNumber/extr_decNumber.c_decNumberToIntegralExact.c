#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uInt ;
struct TYPE_24__ {scalar_t__ exponent; int /*<<< orphan*/  digits; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_25__ {int /*<<< orphan*/  status; scalar_t__ traps; int /*<<< orphan*/  digits; } ;
typedef  TYPE_2__ decContext ;

/* Variables and functions */
 int /*<<< orphan*/  DECUNUSED ; 
 scalar_t__ SPECIALARG ; 
 scalar_t__ decCheckOperands (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  decNaNs (TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* decNumberCopy (TYPE_1__*,TYPE_1__ const*) ; 
 scalar_t__ decNumberIsInfinite (TYPE_1__ const*) ; 
 int /*<<< orphan*/  decNumberQuantize (TYPE_1__*,TYPE_1__ const*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 
 int /*<<< orphan*/  decStatus (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 

decNumber * decNumberToIntegralExact(decNumber *res, const decNumber *rhs,
                                     decContext *set) {
  decNumber dn;
  decContext workset;              // working context
  uInt status=0;                   // accumulator

  #if DECCHECK
  if (decCheckOperands(res, DECUNUSED, rhs, set)) return res;
  #endif

  // handle infinities and NaNs
  if (SPECIALARG) {
    if (decNumberIsInfinite(rhs)) decNumberCopy(res, rhs); // an Infinity
     else decNaNs(res, rhs, NULL, set, &status); // a NaN
    }
   else { // finite
    // have a finite number; no error possible (res must be big enough)
    if (rhs->exponent>=0) return decNumberCopy(res, rhs);
    // that was easy, but if negative exponent there is work to do...
    workset=*set;                  // clone rounding, etc.
    workset.digits=rhs->digits;    // no length rounding
    workset.traps=0;               // no traps
    decNumberZero(&dn);            // make a number with exponent 0
    decNumberQuantize(res, rhs, &dn, &workset);
    status|=workset.status;
    }
  if (status!=0) decStatus(res, status, set);
  return res;
  }