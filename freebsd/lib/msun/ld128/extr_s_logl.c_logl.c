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
struct ld {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOPRINT_START (long double*) ; 
 int /*<<< orphan*/  ENTERI () ; 
 int /*<<< orphan*/  RETURNSPI (struct ld*) ; 
 int /*<<< orphan*/  k_logl (long double,struct ld*) ; 

long double
logl(long double x)
{
	struct ld r;

	ENTERI();
	DOPRINT_START(&x);
	k_logl(x, &r);
	RETURNSPI(&r);
}