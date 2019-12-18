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
typedef  scalar_t__ Int ;

/* Variables and functions */
 scalar_t__ DECEMIN ; 
 scalar_t__ DFISSPECIAL (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISZERO (int /*<<< orphan*/  const*) ; 
 scalar_t__ GETEXPUN (int /*<<< orphan*/  const*) ; 
 scalar_t__ decFloatDigits (int /*<<< orphan*/  const*) ; 

uInt decFloatIsNormal(const decFloat *df) {
  Int exp;                         // exponent
  if (DFISSPECIAL(df)) return 0;
  if (DFISZERO(df)) return 0;
  // is finite and non-zero
  exp=GETEXPUN(df)                 // get unbiased exponent ..
     +decFloatDigits(df)-1;        // .. and make adjusted exponent
  return (exp>=DECEMIN);           // < DECEMIN is subnormal
  }