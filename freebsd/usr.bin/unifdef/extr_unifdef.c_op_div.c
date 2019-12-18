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
typedef  scalar_t__ Linetype ;

/* Variables and functions */
 scalar_t__ LT_ERROR ; 
 scalar_t__ LT_TRUE ; 
 int /*<<< orphan*/  debug (char*) ; 
 scalar_t__ op_strict (long*,long,scalar_t__,scalar_t__) ; 

__attribute__((used)) static Linetype op_div(long *p, Linetype at, long a, Linetype bt, long b) {
	if (bt != LT_TRUE) {
		debug("eval division by zero");
		return (LT_ERROR);
	}
	return op_strict(p, a / b, at, bt);
}