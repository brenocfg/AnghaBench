#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ exponent; int* lsu; scalar_t__ bits; int /*<<< orphan*/  digits; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_17__ {int /*<<< orphan*/  digits; } ;
typedef  TYPE_2__ decContext ;
typedef  int Unit ;
typedef  size_t Int ;

/* Variables and functions */
 int D2U (int /*<<< orphan*/ ) ; 
 size_t DECDPUN ; 
 int /*<<< orphan*/  DEC_Invalid_operation ; 
 size_t MSUDIGITS (int /*<<< orphan*/ ) ; 
 scalar_t__ decCheckOperands (TYPE_1__*,TYPE_1__ const*,TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  decGetDigits (int*,int) ; 
 scalar_t__ decNumberIsNegative (TYPE_1__ const*) ; 
 scalar_t__ decNumberIsSpecial (TYPE_1__ const*) ; 
 int /*<<< orphan*/  decStatus (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__* powers ; 

decNumber * decNumberOr(decNumber *res, const decNumber *lhs,
                        const decNumber *rhs, decContext *set) {
  const Unit *ua, *ub;                  // -> operands
  const Unit *msua, *msub;              // -> operand msus
  Unit  *uc, *msuc;                     // -> result and its msu
  Int   msudigs;                        // digits in res msu
  #if DECCHECK
  if (decCheckOperands(res, lhs, rhs, set)) return res;
  #endif

  if (lhs->exponent!=0 || decNumberIsSpecial(lhs) || decNumberIsNegative(lhs)
   || rhs->exponent!=0 || decNumberIsSpecial(rhs) || decNumberIsNegative(rhs)) {
    decStatus(res, DEC_Invalid_operation, set);
    return res;
    }
  // operands are valid
  ua=lhs->lsu;                          // bottom-up
  ub=rhs->lsu;                          // ..
  uc=res->lsu;                          // ..
  msua=ua+D2U(lhs->digits)-1;           // -> msu of lhs
  msub=ub+D2U(rhs->digits)-1;           // -> msu of rhs
  msuc=uc+D2U(set->digits)-1;           // -> msu of result
  msudigs=MSUDIGITS(set->digits);       // [faster than remainder]
  for (; uc<=msuc; ua++, ub++, uc++) {  // Unit loop
    Unit a, b;                          // extract units
    if (ua>msua) a=0;
     else a=*ua;
    if (ub>msub) b=0;
     else b=*ub;
    *uc=0;                              // can now write back
    if (a|b) {                          // maybe 1 bits to examine
      Int i, j;
      // This loop could be unrolled and/or use BIN2BCD tables
      for (i=0; i<DECDPUN; i++) {
        if ((a|b)&1) *uc=*uc+(Unit)powers[i];     // effect OR
        j=a%10;
        a=a/10;
        j|=b%10;
        b=b/10;
        if (j>1) {
          decStatus(res, DEC_Invalid_operation, set);
          return res;
          }
        if (uc==msuc && i==msudigs-1) break;      // just did final digit
        } // each digit
      } // non-zero
    } // each unit
  // [here uc-1 is the msu of the result]
  res->digits=decGetDigits(res->lsu, uc-res->lsu);
  res->exponent=0;                      // integer
  res->bits=0;                          // sign=0
  return res;  // [no status to set]
  }