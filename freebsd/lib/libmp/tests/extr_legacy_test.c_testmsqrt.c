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
 int /*<<< orphan*/  c0 ; 
 int /*<<< orphan*/  c25 ; 
 int /*<<< orphan*/  c42 ; 
 int /*<<< orphan*/  c5 ; 
 int /*<<< orphan*/  c6 ; 
 int /*<<< orphan*/  mp_msqrt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t0 ; 
 int /*<<< orphan*/  t1 ; 
 int /*<<< orphan*/  testmcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
testmsqrt(void)
{

	mp_msqrt(c25, t0, t1);
	testmcmp(t0, c5, "msqrt0");
	testmcmp(t1, c0, "msqrt1");
	mp_msqrt(c42, t0, t1);
	testmcmp(t0, c6, "msqrt2");
	testmcmp(t1, c6, "msqrt3");
}