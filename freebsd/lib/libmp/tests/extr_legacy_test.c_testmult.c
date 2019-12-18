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
 int /*<<< orphan*/  c14 ; 
 int /*<<< orphan*/  c2 ; 
 int /*<<< orphan*/  c3 ; 
 int /*<<< orphan*/  c42 ; 
 int /*<<< orphan*/  c5 ; 
 int /*<<< orphan*/  mp_mult (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t0 ; 
 int /*<<< orphan*/  testmcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
testmult(void)
{

	mp_mult(c5, c2, t0);
	testmcmp(t0, c10, "mmult0");
	mp_mult(c3, c14, t0);
	testmcmp(t0, c42, "mmult1");
}