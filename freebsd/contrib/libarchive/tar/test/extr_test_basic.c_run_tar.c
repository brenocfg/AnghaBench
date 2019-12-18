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
 int /*<<< orphan*/  assertChdir (char const*) ; 
 int /*<<< orphan*/  assertEmptyFile (char*) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertMakeDir (char const*,int) ; 
 int /*<<< orphan*/  failure (char*,int /*<<< orphan*/ ,char const*) ; 
 int systemf (char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  testprog ; 

__attribute__((used)) static void
run_tar(const char *target, const char *pack_options,
    const char *unpack_options, const char *flist)
{
	int r;

	assertMakeDir(target, 0775);

	/* Use the tar program to create an archive. */
	r = systemf("%s cf - %s %s >%s/archive 2>%s/pack.err", testprog, pack_options, flist, target, target);
	failure("Error invoking %s cf -", testprog, pack_options);
	assertEqualInt(r, 0);

	assertChdir(target);

	/* Verify that nothing went to stderr. */
	assertEmptyFile("pack.err");

	/*
	 * Use tar to unpack the archive into another directory.
	 */
	r = systemf("%s xf archive %s >unpack.out 2>unpack.err",
	    testprog, unpack_options);
	failure("Error invoking %s xf archive %s", testprog, unpack_options);
	assertEqualInt(r, 0);

	/* Verify that nothing went to stderr. */
	assertEmptyFile("unpack.err");
	assertChdir("..");
}