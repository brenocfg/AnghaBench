#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
typedef  int /*<<< orphan*/  uByte ;
typedef  int /*<<< orphan*/  decFloat ;
struct TYPE_8__ {int status; } ;
typedef  TYPE_1__ decContext ;
struct TYPE_9__ {int sign; int /*<<< orphan*/  exponent; int /*<<< orphan*/ * msd; int /*<<< orphan*/ * lsd; } ;
typedef  TYPE_2__ bcdnum ;
typedef  int Int ;

/* Variables and functions */
 int DECFLOAT_Sign ; 
 int DECPMAX ; 
 scalar_t__ DECWORDS ; 
 scalar_t__ DFISINF (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DFISINT (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISNAN (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISSIGNED (int /*<<< orphan*/  const*) ; 
 int DFWORD (int /*<<< orphan*/  const*,scalar_t__) ; 
 int* DPD2BIN ; 
 int /*<<< orphan*/  GETCOEFF (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GETEXPUN (int /*<<< orphan*/  const*) ; 
 int PHALF ; 
 int abs (int) ; 
 int /*<<< orphan*/ * decCanonical (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  decFinalize (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int decFloatDigits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * decInfinity (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * decInvalid (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * decNaNs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

decFloat * decFloatRotate(decFloat *result,
                         const decFloat *dfl, const decFloat *dfr,
                         decContext *set) {
  Int rotate;                           // dfr as an Int
  uByte buf[DECPMAX+PHALF];             // coefficient + half
  uInt digits, savestat;                // work
  bcdnum num;                           // ..
  uByte *ub;                            // ..

  if (DFISNAN(dfl)||DFISNAN(dfr)) return decNaNs(result, dfl, dfr, set);
  if (!DFISINT(dfr)) return decInvalid(result, set);
  digits=decFloatDigits(dfr);                    // calculate digits
  if (digits>2) return decInvalid(result, set);  // definitely out of range
  rotate=DPD2BIN[DFWORD(dfr, DECWORDS-1)&0x3ff]; // is in bottom declet
  if (rotate>DECPMAX) return decInvalid(result, set); // too big
  // [from here on no error or status change is possible]
  if (DFISINF(dfl)) return decInfinity(result, dfl);  // canonical
  // handle no-rotate cases
  if (rotate==0 || rotate==DECPMAX) return decCanonical(result, dfl);
  // a real rotate is needed: 0 < rotate < DECPMAX
  // reduce the rotation to no more than half to reduce copying later
  // (for QUAD in fact half + 2 digits)
  if (DFISSIGNED(dfr)) rotate=-rotate;
  if (abs(rotate)>PHALF) {
    if (rotate<0) rotate=DECPMAX+rotate;
     else rotate=rotate-DECPMAX;
    }
  // now lay out the coefficient, leaving room to the right or the
  // left depending on the direction of rotation
  ub=buf;
  if (rotate<0) ub+=PHALF;    // rotate right, so space to left
  GETCOEFF(dfl, ub);
  // copy half the digits to left or right, and set num.msd
  if (rotate<0) {
    memcpy(buf, buf+DECPMAX, PHALF);
    num.msd=buf+PHALF+rotate;
    }
   else {
    memcpy(buf+DECPMAX, buf, PHALF);
    num.msd=buf+rotate;
    }
  // fill in rest of num
  num.lsd=num.msd+DECPMAX-1;
  num.sign=DFWORD(dfl, 0)&DECFLOAT_Sign;
  num.exponent=GETEXPUN(dfl);
  savestat=set->status;                 // record
  decFinalize(result, &num, set);
  set->status=savestat;                 // restore
  return result;
  }