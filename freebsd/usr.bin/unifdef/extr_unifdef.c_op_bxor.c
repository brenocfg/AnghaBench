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
typedef  int /*<<< orphan*/  Linetype ;

/* Variables and functions */
 int /*<<< orphan*/  op_strict (long*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Linetype op_bxor(long *p, Linetype at, long a, Linetype bt, long b) {
	return op_strict(p, a ^ b, at, bt);
}