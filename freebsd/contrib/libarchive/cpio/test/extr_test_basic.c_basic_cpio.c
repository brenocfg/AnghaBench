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
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertMakeDir (char const*,int) ; 
 int /*<<< orphan*/  assertTextFileContents (char const*,char*) ; 
 int /*<<< orphan*/  failure (char*,char const*,char const*,...) ; 
 int systemf (char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  testprog ; 
 int /*<<< orphan*/  verify_files (char const*) ; 

__attribute__((used)) static void
basic_cpio(const char *target,
    const char *pack_options,
    const char *unpack_options,
    const char *se, const char *se2)
{
	int r;

	if (!assertMakeDir(target, 0775))
	    return;

	/* Use the cpio program to create an archive. */
	r = systemf("%s -R 1000:1000 -o %s < filelist >%s/archive 2>%s/pack.err",
	    testprog, pack_options, target, target);
	failure("Error invoking %s -o %s", testprog, pack_options);
	assertEqualInt(r, 0);

	assertChdir(target);

	/* Verify stderr. */
	failure("Expected: %s, options=%s", se, pack_options);
	assertTextFileContents(se, "pack.err");

	/*
	 * Use cpio to unpack the archive into another directory.
	 */
	r = systemf("%s -i %s< archive >unpack.out 2>unpack.err",
	    testprog, unpack_options);
	failure("Error invoking %s -i %s", testprog, unpack_options);
	assertEqualInt(r, 0);

	/* Verify stderr. */
	failure("Error invoking %s -i %s in dir %s", testprog, unpack_options, target);
	assertTextFileContents(se2, "unpack.err");

	verify_files(pack_options);

	assertChdir("..");
}