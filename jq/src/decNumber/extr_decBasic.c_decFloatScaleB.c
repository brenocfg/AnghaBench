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
typedef  int uInt ;
typedef  int /*<<< orphan*/  decFloat ;
typedef  int /*<<< orphan*/  decContext ;
typedef  int Int ;

/* Variables and functions */
 scalar_t__ DFISINF (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DFISINT (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISNAN (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISSIGNED (int /*<<< orphan*/  const*) ; 
 int DFWORD (int /*<<< orphan*/  const*,int) ; 
 int* DPD2BIN ; 
 scalar_t__ GETEXPUN (int /*<<< orphan*/ *) ; 
 int SCALEBMAX ; 
 int decFloatDigits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * decFloatSetExponent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * decInfinity (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * decInvalid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * decNaNs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

decFloat * decFloatScaleB(decFloat *result,
                          const decFloat *dfl, const decFloat *dfr,
                          decContext *set) {
  uInt digits;                          // work
  Int  expr;                            // dfr as an Int

  if (DFISNAN(dfl)||DFISNAN(dfr)) return decNaNs(result, dfl, dfr, set);
  if (!DFISINT(dfr)) return decInvalid(result, set);
  digits=decFloatDigits(dfr);                // calculate digits

  #if DOUBLE
  if (digits>3) return decInvalid(result, set);   // definitely out of range
  expr=DPD2BIN[DFWORD(dfr, 1)&0x3ff];             // must be in bottom declet
  #elif QUAD
  if (digits>5) return decInvalid(result, set);   // definitely out of range
  expr=DPD2BIN[DFWORD(dfr, 3)&0x3ff]              // in bottom 2 declets ..
      +DPD2BIN[(DFWORD(dfr, 3)>>10)&0x3ff]*1000;  // ..
  #endif
  if (expr>SCALEBMAX) return decInvalid(result, set);  // oops
  // [from now on no error possible]
  if (DFISINF(dfl)) return decInfinity(result, dfl);   // canonical
  if (DFISSIGNED(dfr)) expr=-expr;
  // dfl is finite and expr is valid
  *result=*dfl;                              // copy to target
  return decFloatSetExponent(result, set, GETEXPUN(result)+expr);
  }