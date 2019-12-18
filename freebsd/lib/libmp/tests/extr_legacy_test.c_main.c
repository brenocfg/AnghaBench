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
 int EX_OK ; 
 int /*<<< orphan*/  c0 ; 
 int /*<<< orphan*/  c1 ; 
 int /*<<< orphan*/  c10 ; 
 int /*<<< orphan*/  c14 ; 
 int /*<<< orphan*/  c15 ; 
 int /*<<< orphan*/  c2 ; 
 int /*<<< orphan*/  c25 ; 
 int /*<<< orphan*/  c3 ; 
 int /*<<< orphan*/  c42 ; 
 int /*<<< orphan*/  c43 ; 
 int /*<<< orphan*/  c44 ; 
 int /*<<< orphan*/  c45 ; 
 int /*<<< orphan*/  c5 ; 
 int /*<<< orphan*/  c6 ; 
 int /*<<< orphan*/  c8 ; 
 int /*<<< orphan*/  mp_itom (int) ; 
 int /*<<< orphan*/  mp_mfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  t0 ; 
 int /*<<< orphan*/  t1 ; 
 int /*<<< orphan*/  testdiv () ; 
 int /*<<< orphan*/  testgcd () ; 
 int /*<<< orphan*/  testmsqrt () ; 
 int /*<<< orphan*/  testmult () ; 
 int /*<<< orphan*/  testpow () ; 
 int /*<<< orphan*/  testsimpel () ; 

int
main(int argc, char *argv[])
{

	printf("1..25\n");

	/*
	 * Init "constants" variables - done in this somewhat
	 * cumbersome way to in theory be able to check for memory
	 * leaks.
	 */
	c0 = mp_itom(0);
	c1 = mp_itom(1);
	c2 = mp_itom(2);
	c3 = mp_itom(3);
	c5 = mp_itom(5);
	c6 = mp_itom(6);
	c8 = mp_itom(8);
	c10 = mp_itom(10);
	c14 = mp_itom(14);
	c15 = mp_itom(15);
	c25 = mp_itom(25);
	c42 = mp_itom(42);
	c43 = mp_itom(43);
	c44 = mp_itom(44);
	c45 = mp_itom(45);

	// Init temp variables
	t0 = mp_itom(0);
	t1 = mp_itom(0);

	// Run tests
	testsimpel();
	testgcd();
	testdiv();
	testmult();
	testpow();
	testmsqrt();

	// Cleanup
	mp_mfree(c0);
	mp_mfree(c1);
	mp_mfree(c2);
	mp_mfree(c3);
	mp_mfree(c5);
	mp_mfree(c6);
	mp_mfree(c8);
	mp_mfree(c10);
	mp_mfree(c14);
	mp_mfree(c15);
	mp_mfree(c25);
	mp_mfree(c42);
	mp_mfree(c43);
	mp_mfree(c44);
	mp_mfree(c45);
	mp_mfree(t0);
	mp_mfree(t1);

	return (EX_OK);
}