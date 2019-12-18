#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uInt ;
struct TYPE_23__ {scalar_t__ digits; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_24__ {scalar_t__ digits; int /*<<< orphan*/  extended; } ;
typedef  TYPE_2__ decContext ;

/* Variables and functions */
 int /*<<< orphan*/  DECUNUSED ; 
 int /*<<< orphan*/  decCheckInexact (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  decCheckMath (TYPE_1__ const*,TYPE_2__*,scalar_t__*) ; 
 scalar_t__ decCheckOperands (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  decExpOp (TYPE_1__*,TYPE_1__ const*,TYPE_2__*,scalar_t__*) ; 
 TYPE_1__* decRoundOperand (TYPE_1__ const*,TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  decStatus (TYPE_1__*,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

decNumber * decNumberExp(decNumber *res, const decNumber *rhs,
                         decContext *set) {
  uInt status=0;                        // accumulator
  #if DECSUBSET
  decNumber *allocrhs=NULL;        // non-NULL if rounded rhs allocated
  #endif

  #if DECCHECK
  if (decCheckOperands(res, DECUNUSED, rhs, set)) return res;
  #endif

  // Check restrictions; these restrictions ensure that if h=8 (see
  // decExpOp) then the result will either overflow or underflow to 0.
  // Other math functions restrict the input range, too, for inverses.
  // If not violated then carry out the operation.
  if (!decCheckMath(rhs, set, &status)) do { // protect allocation
    #if DECSUBSET
    if (!set->extended) {
      // reduce operand and set lostDigits status, as needed
      if (rhs->digits>set->digits) {
        allocrhs=decRoundOperand(rhs, set, &status);
        if (allocrhs==NULL) break;
        rhs=allocrhs;
        }
      }
    #endif
    decExpOp(res, rhs, set, &status);
    } while(0);                         // end protected

  #if DECSUBSET
  if (allocrhs !=NULL) free(allocrhs);  // drop any storage used
  #endif
  // apply significant status
  if (status!=0) decStatus(res, status, set);
  #if DECCHECK
  decCheckInexact(res, set);
  #endif
  return res;
  }