#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
typedef  enum rounding { ____Placeholder_rounding } rounding ;
typedef  int /*<<< orphan*/  decFloat ;
struct TYPE_5__ {int round; int status; } ;
typedef  TYPE_1__ decContext ;
typedef  scalar_t__ Int ;
typedef  int /*<<< orphan*/  Flag ;

/* Variables and functions */
 scalar_t__ DECBIAS ; 
 scalar_t__* DECCOMBEXP ; 
 scalar_t__ DFISNAN (int /*<<< orphan*/  const*) ; 
 int DFWORD (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXPISSPECIAL (scalar_t__) ; 
 scalar_t__ GETECON (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * decCanonical (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  decFloatQuantize (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  decFloatZero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * decInfinity (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * decNaNs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static decFloat * decToIntegral(decFloat *result, const decFloat *df,
                                decContext *set, enum rounding rmode,
                                Flag exact) {
  Int  exp;                        // exponent
  uInt sourhi;                     // top word from source decFloat
  enum rounding saveround;         // saver
  uInt savestatus;                 // ..
  decFloat zero;                   // work

  /* Start decoding the argument */
  sourhi=DFWORD(df, 0);            // top word
  exp=DECCOMBEXP[sourhi>>26];      // get exponent high bits (in place)

  if (EXPISSPECIAL(exp)) {         // is special?
    // NaNs are handled as usual
    if (DFISNAN(df)) return decNaNs(result, df, NULL, set);
    // must be infinite; return canonical infinity with sign of df
    return decInfinity(result, df);
    }

  /* Here when the argument is finite */
  // complete extraction of the exponent
  exp+=GETECON(df)-DECBIAS;             // .. + continuation and unbias

  if (exp>=0) return decCanonical(result, df); // already integral

  saveround=set->round;                 // save rounding mode ..
  savestatus=set->status;               // .. and status
  set->round=rmode;                     // set mode
  decFloatZero(&zero);                  // make 0E+0
  decFloatQuantize(result, df, &zero, set); // 'integrate'; cannot fail
  set->round=saveround;                 // restore rounding mode ..
  if (!exact) set->status=savestatus;   // .. and status, unless exact
  return result;
  }