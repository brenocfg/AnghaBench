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
 int /*<<< orphan*/  c10 ; 
 int /*<<< orphan*/  c2 ; 
 int /*<<< orphan*/  c3 ; 
 int /*<<< orphan*/  c8 ; 
 int /*<<< orphan*/  mp_pow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_rpow (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t0 ; 
 int /*<<< orphan*/  testmcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
testpow(void)
{

	mp_pow(c2, c3, c10, t0);
	testmcmp(t0, c8, "pow0");
	mp_pow(c2, c3, c3, t0);
	testmcmp(t0, c2, "pow1");
	mp_rpow(c2, 3, t0);
	testmcmp(t0, c8, "rpow0");
}