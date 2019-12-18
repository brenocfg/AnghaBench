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
typedef  enum decClass { ____Placeholder_decClass } decClass ;
typedef  int /*<<< orphan*/  decFloat ;
typedef  scalar_t__ Int ;

/* Variables and functions */
 scalar_t__ DECEMIN ; 
 int DEC_CLASS_NEG_INF ; 
 int DEC_CLASS_NEG_NORMAL ; 
 int DEC_CLASS_NEG_SUBNORMAL ; 
 int DEC_CLASS_NEG_ZERO ; 
 int DEC_CLASS_POS_INF ; 
 int DEC_CLASS_POS_NORMAL ; 
 int DEC_CLASS_POS_SUBNORMAL ; 
 int DEC_CLASS_POS_ZERO ; 
 int DEC_CLASS_QNAN ; 
 int DEC_CLASS_SNAN ; 
 scalar_t__ DFISQNAN (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISSIGNED (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISSNAN (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISSPECIAL (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISZERO (int /*<<< orphan*/  const*) ; 
 scalar_t__ GETEXPUN (int /*<<< orphan*/  const*) ; 
 scalar_t__ decFloatDigits (int /*<<< orphan*/  const*) ; 

enum decClass decFloatClass(const decFloat *df) {
  Int exp;                         // exponent
  if (DFISSPECIAL(df)) {
    if (DFISQNAN(df)) return DEC_CLASS_QNAN;
    if (DFISSNAN(df)) return DEC_CLASS_SNAN;
    // must be an infinity
    if (DFISSIGNED(df)) return DEC_CLASS_NEG_INF;
    return DEC_CLASS_POS_INF;
    }
  if (DFISZERO(df)) {              // quite common
    if (DFISSIGNED(df)) return DEC_CLASS_NEG_ZERO;
    return DEC_CLASS_POS_ZERO;
    }
  // is finite and non-zero; similar code to decFloatIsNormal, here
  // [this could be speeded up slightly by in-lining decFloatDigits]
  exp=GETEXPUN(df)                 // get unbiased exponent ..
     +decFloatDigits(df)-1;        // .. and make adjusted exponent
  if (exp>=DECEMIN) {              // is normal
    if (DFISSIGNED(df)) return DEC_CLASS_NEG_NORMAL;
    return DEC_CLASS_POS_NORMAL;
    }
  // is subnormal
  if (DFISSIGNED(df)) return DEC_CLASS_NEG_SUBNORMAL;
  return DEC_CLASS_POS_SUBNORMAL;
  }