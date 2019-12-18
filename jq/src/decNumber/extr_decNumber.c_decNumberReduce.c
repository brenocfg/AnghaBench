#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uInt ;
struct TYPE_27__ {scalar_t__ digits; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_28__ {scalar_t__ digits; int /*<<< orphan*/  extended; } ;
typedef  TYPE_2__ decContext ;
typedef  int /*<<< orphan*/  Int ;

/* Variables and functions */
 int /*<<< orphan*/  DECUNUSED ; 
 scalar_t__ decCheckOperands (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  decCopyFit (TYPE_1__*,TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  decFinish (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  decNaNs (TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ *,TYPE_2__*,scalar_t__*) ; 
 scalar_t__ decNumberIsNaN (TYPE_1__ const*) ; 
 TYPE_1__* decRoundOperand (TYPE_1__ const*,TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  decStatus (TYPE_1__*,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  decTrim (TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

decNumber * decNumberReduce(decNumber *res, const decNumber *rhs,
                            decContext *set) {
  #if DECSUBSET
  decNumber *allocrhs=NULL;        // non-NULL if rounded rhs allocated
  #endif
  uInt status=0;                   // as usual
  Int  residue=0;                  // as usual
  Int  dropped;                    // work

  #if DECCHECK
  if (decCheckOperands(res, DECUNUSED, rhs, set)) return res;
  #endif

  do {                             // protect allocated storage
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
    // [following code does not require input rounding]

    // Infinities copy through; NaNs need usual treatment
    if (decNumberIsNaN(rhs)) {
      decNaNs(res, rhs, NULL, set, &status);
      break;
      }

    // reduce result to the requested length and copy to result
    decCopyFit(res, rhs, set, &residue, &status); // copy & round
    decFinish(res, set, &residue, &status);       // cleanup/set flags
    decTrim(res, set, 1, 0, &dropped);            // normalize in place
                                                  // [may clamp]
    } while(0);                              // end protected

  #if DECSUBSET
  if (allocrhs !=NULL) free(allocrhs);       // ..
  #endif
  if (status!=0) decStatus(res, status, set);// then report status
  return res;
  }