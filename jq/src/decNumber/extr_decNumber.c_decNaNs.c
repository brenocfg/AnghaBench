#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
struct TYPE_11__ {int bits; int digits; scalar_t__ exponent; int /*<<< orphan*/ * lsu; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_12__ {int digits; } ;
typedef  TYPE_2__ decContext ;
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int D2U (int) ; 
 int DECDPUN ; 
 int DECNAN ; 
 int DECSNAN ; 
 int DEC_Invalid_operation ; 
 int DEC_sNaN ; 
 int /*<<< orphan*/  decDecap (TYPE_1__*,int) ; 
 int /*<<< orphan*/  decNumberCopy (TYPE_1__*,TYPE_1__ const*) ; 

__attribute__((used)) static decNumber * decNaNs(decNumber *res, const decNumber *lhs,
                           const decNumber *rhs, decContext *set,
                           uInt *status) {
  // This decision tree ends up with LHS being the source pointer,
  // and status updated if need be
  if (lhs->bits & DECSNAN)
    *status|=DEC_Invalid_operation | DEC_sNaN;
   else if (rhs==NULL);
   else if (rhs->bits & DECSNAN) {
    lhs=rhs;
    *status|=DEC_Invalid_operation | DEC_sNaN;
    }
   else if (lhs->bits & DECNAN);
   else lhs=rhs;

  // propagate the payload
  if (lhs->digits<=set->digits) decNumberCopy(res, lhs); // easy
   else { // too long
    const Unit *ul;
    Unit *ur, *uresp1;
    // copy safe number of units, then decapitate
    res->bits=lhs->bits;                // need sign etc.
    uresp1=res->lsu+D2U(set->digits);
    for (ur=res->lsu, ul=lhs->lsu; ur<uresp1; ur++, ul++) *ur=*ul;
    res->digits=D2U(set->digits)*DECDPUN;
    // maybe still too long
    if (res->digits>set->digits) decDecap(res, res->digits-set->digits);
    }

  res->bits&=~DECSNAN;        // convert any sNaN to NaN, while
  res->bits|=DECNAN;          // .. preserving sign
  res->exponent=0;            // clean exponent
                              // [coefficient was copied/decapitated]
  return res;
  }