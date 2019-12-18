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
typedef  int /*<<< orphan*/  decNumber ;
struct TYPE_4__ {int status; scalar_t__ traps; } ;
typedef  TYPE_1__ decContext ;

/* Variables and functions */
 int DEC_Invalid_operation ; 
 int /*<<< orphan*/  decNumberToIntegralExact (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ; 

decNumber * decNumberToIntegralValue(decNumber *res, const decNumber *rhs,
                                     decContext *set) {
  decContext workset=*set;         // working context
  workset.traps=0;                 // no traps
  decNumberToIntegralExact(res, rhs, &workset);
  // this never affects set, except for sNaNs; NaN will have been set
  // or propagated already, so no need to call decStatus
  set->status|=workset.status&DEC_Invalid_operation;
  return res;
  }