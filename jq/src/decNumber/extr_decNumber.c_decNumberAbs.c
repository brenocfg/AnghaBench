#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uInt ;
typedef  int /*<<< orphan*/  uByte ;
struct TYPE_13__ {int bits; int /*<<< orphan*/  exponent; } ;
typedef  TYPE_1__ decNumber ;
typedef  int /*<<< orphan*/  decContext ;

/* Variables and functions */
 int DECNEG ; 
 int /*<<< orphan*/  DECUNUSED ; 
 int /*<<< orphan*/  decAddOp (TYPE_1__*,TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  decCheckInexact (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ decCheckOperands (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 
 int /*<<< orphan*/  decStatus (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 

decNumber * decNumberAbs(decNumber *res, const decNumber *rhs,
                         decContext *set) {
  decNumber dzero;                      // for 0
  uInt status=0;                        // accumulator

  #if DECCHECK
  if (decCheckOperands(res, DECUNUSED, rhs, set)) return res;
  #endif

  decNumberZero(&dzero);                // set 0
  dzero.exponent=rhs->exponent;         // [no coefficient expansion]
  decAddOp(res, &dzero, rhs, set, (uByte)(rhs->bits & DECNEG), &status);
  if (status!=0) decStatus(res, status, set);
  #if DECCHECK
  decCheckInexact(res, set);
  #endif
  return res;
  }