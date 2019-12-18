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
struct TYPE_24__ {scalar_t__ digits; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_25__ {scalar_t__ digits; int /*<<< orphan*/  extended; } ;
typedef  TYPE_2__ decContext ;

/* Variables and functions */
 int /*<<< orphan*/  DECUNUSED ; 
 int /*<<< orphan*/  DEC_Invalid_operation ; 
 scalar_t__ ISZERO (TYPE_1__ const*) ; 
 int /*<<< orphan*/  decCheckInexact (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  decCheckMath (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ decCheckOperands (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  decLnOp (TYPE_1__*,TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* decRoundOperand (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decStatus (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

decNumber * decNumberLn(decNumber *res, const decNumber *rhs,
                        decContext *set) {
  uInt status=0;                   // accumulator
  #if DECSUBSET
  decNumber *allocrhs=NULL;        // non-NULL if rounded rhs allocated
  #endif

  #if DECCHECK
  if (decCheckOperands(res, DECUNUSED, rhs, set)) return res;
  #endif

  // Check restrictions; this is a math function; if not violated
  // then carry out the operation.
  if (!decCheckMath(rhs, set, &status)) do { // protect allocation
    #if DECSUBSET
    if (!set->extended) {
      // reduce operand and set lostDigits status, as needed
      if (rhs->digits>set->digits) {
        allocrhs=decRoundOperand(rhs, set, &status);
        if (allocrhs==NULL) break;
        rhs=allocrhs;
        }
      // special check in subset for rhs=0
      if (ISZERO(rhs)) {                // +/- zeros -> error
        status|=DEC_Invalid_operation;
        break;}
      } // extended=0
    #endif
    decLnOp(res, rhs, set, &status);
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