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
 int /*<<< orphan*/  LIMIT_NONE ; 
 int /*<<< orphan*/  assertEmptyFile (char*) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertMakeDir (char*,int) ; 
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  failure (char*,int /*<<< orphan*/ ) ; 
 int systemf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testprog ; 
 int /*<<< orphan*/  verify_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
copy_basic(void)
{
	int r;

	/* NOTE: for proper operation on cygwin-1.5 and windows, the
	 * length of the name of the directory below, "plain", must be
	 * less than or equal to the length of the name of the original
	 * directory, "original"  This restriction derives from the
	 * extremely limited pathname lengths on those platforms.
	 */
	assertMakeDir("plain", 0775);
	assertEqualInt(0, chdir("plain"));

	/*
	 * Use the tar program to create an archive.
	 */
	r = systemf("%s cf archive -C ../original f d l m s >pack.out 2>pack.err",
	    testprog);
	failure("Error invoking \"%s cf\"", testprog);
	assertEqualInt(r, 0);

	/* Verify that nothing went to stdout or stderr. */
	assertEmptyFile("pack.err");
	assertEmptyFile("pack.out");

	/*
	 * Use tar to unpack the archive into another directory.
	 */
	r = systemf("%s xf archive >unpack.out 2>unpack.err", testprog);
	failure("Error invoking %s xf archive", testprog);
	assertEqualInt(r, 0);

	/* Verify that nothing went to stdout or stderr. */
	assertEmptyFile("unpack.err");
	assertEmptyFile("unpack.out");

	verify_tree(LIMIT_NONE);
	assertEqualInt(0, chdir(".."));
}