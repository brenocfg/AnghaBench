#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uByte ;
struct TYPE_10__ {int bits; } ;
typedef  TYPE_1__ decNumber ;

/* Variables and functions */
 int DECNEG ; 
 int /*<<< orphan*/  DECUNCONT ; 
 int /*<<< orphan*/  DECUNUSED ; 
 scalar_t__ decCheckOperands (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decNumberCopy (TYPE_1__*,TYPE_1__ const*) ; 

decNumber * decNumberCopySign(decNumber *res, const decNumber *lhs,
                              const decNumber *rhs) {
  uByte sign;                           // rhs sign
  #if DECCHECK
  if (decCheckOperands(res, DECUNUSED, rhs, DECUNCONT)) return res;
  #endif
  sign=rhs->bits & DECNEG;              // save sign bit
  decNumberCopy(res, lhs);
  res->bits&=~DECNEG;                   // clear the sign
  res->bits|=sign;                      // set from rhs
  return res;
  }