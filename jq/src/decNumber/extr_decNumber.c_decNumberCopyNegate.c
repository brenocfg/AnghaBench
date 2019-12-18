#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ decNumber ;

/* Variables and functions */
 int /*<<< orphan*/  DECNEG ; 
 int /*<<< orphan*/  DECUNCONT ; 
 int /*<<< orphan*/  DECUNUSED ; 
 scalar_t__ decCheckOperands (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decNumberCopy (TYPE_1__*,TYPE_1__ const*) ; 

decNumber * decNumberCopyNegate(decNumber *res, const decNumber *rhs) {
  #if DECCHECK
  if (decCheckOperands(res, DECUNUSED, rhs, DECUNCONT)) return res;
  #endif
  decNumberCopy(res, rhs);
  res->bits^=DECNEG;                    // invert the sign
  return res;
  }