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
 double INFINITY ; 
 double NAN ; 
 char* comment ; 
 double nextafterf (double,double) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  testall (int,double,double) ; 

int
main(void)
{

	printf("1..12\n");

	testall(1, 1.0, 0.0);
	testall(2, 42.0, nextafterf(42.0, -INFINITY));
	testall(3, nextafterf(42.0, INFINITY), 42.0);
	testall(4, -5.0, -5.0);
	testall(5, -3.0, -4.0);
#ifdef affected_by_bug_208703
	comment = "# TODO: testcase 6-7 fails invariant with clang 3.8+ (bug 208703)";
#endif
	testall(6, 1.0, NAN);
	testall(7, INFINITY, NAN);
	comment = NULL;
	testall(8, INFINITY, 1.0);
	testall(9, -3.0, -INFINITY);
	testall(10, 3.0, -INFINITY);
#ifdef affected_by_bug_208703
	comment = "# TODO: testcase 11-12 fails invariant with clang 3.8+ (bug 208703)";
#endif
	testall(11, NAN, NAN);

	/* This test isn't strictly required to work by C99. */
	testall(12, 0.0, -0.0);
	comment = NULL;

	return (0);
}