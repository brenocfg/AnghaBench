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
typedef  scalar_t__ uInt ;
typedef  int /*<<< orphan*/  decNumber ;
typedef  int /*<<< orphan*/  decContext ;

/* Variables and functions */
 int /*<<< orphan*/  REMNEAR ; 
 int /*<<< orphan*/  decCheckInexact (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decDivideOp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  decStatus (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

decNumber * decNumberRemainderNear(decNumber *res, const decNumber *lhs,
                                   const decNumber *rhs, decContext *set) {
  uInt status=0;                        // accumulator
  decDivideOp(res, lhs, rhs, set, REMNEAR, &status);
  if (status!=0) decStatus(res, status, set);
  #if DECCHECK
  decCheckInexact(res, set);
  #endif
  return res;
  }