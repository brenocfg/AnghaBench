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
 int /*<<< orphan*/  assertFileContents (char*,int,char*) ; 
 int /*<<< orphan*/  assertFileNLinks (char*,int) ; 
 int /*<<< orphan*/  assertFileSize (char*,int) ; 
 int /*<<< orphan*/  assertIsDir (char*,int) ; 
 int /*<<< orphan*/  assertIsHardlink (char*,char*) ; 
 int /*<<< orphan*/  assertIsReg (char*,int) ; 
 int /*<<< orphan*/  assertIsSymlink (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ canSymlink () ; 
 int /*<<< orphan*/  failure (char*,char const*) ; 

__attribute__((used)) static void
verify_files(const char *target)
{
	assertChdir(target);

	/* Regular file with 2 links. */
	failure("%s", target);
	assertIsReg("file", -1);
	failure("%s", target);
	assertFileSize("file", 10);
	failure("%s", target);
	assertFileContents("123456789", 10, "file");
	failure("%s", target);
	assertFileNLinks("file", 2);

	/* Another name for the same file. */
	failure("%s", target);
	assertIsReg("linkfile", -1);
	failure("%s", target);
	assertFileSize("linkfile", 10);
	assertFileContents("123456789", 10, "linkfile");
	assertFileNLinks("linkfile", 2);
	assertIsHardlink("file", "linkfile");

	/* Symlink */
	if (canSymlink())
		assertIsSymlink("symlink", "file", 0);

	/* dir */
	failure("%s", target);
	assertIsDir("dir", 0775);
	assertChdir("..");
}