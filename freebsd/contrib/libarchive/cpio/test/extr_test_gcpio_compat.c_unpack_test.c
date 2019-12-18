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
 int /*<<< orphan*/  assertFileNLinks (char*,int) ; 
 int /*<<< orphan*/  assertFileSize (char*,int) ; 
 int /*<<< orphan*/  assertIsDir (char*,int) ; 
 int /*<<< orphan*/  assertIsHardlink (char*,char*) ; 
 int /*<<< orphan*/  assertIsReg (char*,int) ; 
 int /*<<< orphan*/  assertIsSymlink (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertMakeDir (char const*,int) ; 
 int /*<<< orphan*/  assertTextFileContents (char const*,char*) ; 
 scalar_t__ canSymlink () ; 
 int /*<<< orphan*/  extract_reference_file (char const*) ; 
 int /*<<< orphan*/  failure (char*,char const*,...) ; 
 int systemf (char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  testprog ; 

__attribute__((used)) static void
unpack_test(const char *from, const char *options, const char *se)
{
	int r;

	/* Create a work dir named after the file we're unpacking. */
	assertMakeDir(from, 0775);
	assertChdir(from);

	/*
	 * Use cpio to unpack the sample archive
	 */
	extract_reference_file(from);
	r = systemf("%s -i %s < %s >unpack.out 2>unpack.err",
	    testprog, options, from);
	failure("Error invoking %s -i %s < %s",
	    testprog, options, from);
	assertEqualInt(r, 0);

	/* Verify that nothing went to stderr. */
	if (canSymlink()) {
		failure("Error invoking %s -i %s < %s",
		    testprog, options, from);
		assertTextFileContents(se, "unpack.err");
	}

	/*
	 * Verify unpacked files.
	 */

	/* Regular file with 2 links. */
	assertIsReg("file", 0644);
	failure("%s", from);
	assertFileSize("file", 10);
	assertFileSize("linkfile", 10);
	failure("%s", from);
	assertFileNLinks("file", 2);

	/* Another name for the same file. */
	failure("%s", from);
	assertIsHardlink("linkfile", "file");
	assertFileSize("file", 10);
	assertFileSize("linkfile", 10);

	/* Symlink */
	if (canSymlink())
		assertIsSymlink("symlink", "file", 0);

	/* dir */
	assertIsDir("dir", 0775);

	assertChdir("..");
}