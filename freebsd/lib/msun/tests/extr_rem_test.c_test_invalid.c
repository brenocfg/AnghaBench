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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int isnan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remainder (long double,long double) ; 
 int /*<<< orphan*/  remainderf (long double,long double) ; 
 int /*<<< orphan*/  remainderl (long double,long double) ; 
 int /*<<< orphan*/  remquo (long double,long double,int*) ; 
 int /*<<< orphan*/  remquof (long double,long double,int*) ; 
 int /*<<< orphan*/  remquol (long double,long double,int*) ; 

__attribute__((used)) static void
test_invalid(long double x, long double y)
{
	int q;

	q = 0xdeadbeef;

	assert(isnan(remainder(x, y)));
	assert(isnan(remquo(x, y, &q)));
#ifdef STRICT
	assert(q == 0xdeadbeef);
#endif

	assert(isnan(remainderf(x, y)));
	assert(isnan(remquof(x, y, &q)));
#ifdef STRICT
	assert(q == 0xdeadbeef);
#endif

	assert(isnan(remainderl(x, y)));
	assert(isnan(remquol(x, y, &q)));
#ifdef STRICT
	assert(q == 0xdeadbeef);
#endif
}