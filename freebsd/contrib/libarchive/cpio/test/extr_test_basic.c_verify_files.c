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
 int /*<<< orphan*/  assertFileNLinks (char*,int) ; 
 int /*<<< orphan*/  assertFileSize (char*,int) ; 
 int /*<<< orphan*/  assertIsDir (char*,int) ; 
 int /*<<< orphan*/  assertIsHardlink (char*,char*) ; 
 int /*<<< orphan*/  assertIsReg (char*,int) ; 
 int /*<<< orphan*/  assertIsSymlink (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ canSymlink () ; 
 int /*<<< orphan*/  failure (char const*) ; 

__attribute__((used)) static void
verify_files(const char *msg)
{
	/*
	 * Verify unpacked files.
	 */

	/* Regular file with 2 links. */
	failure(msg);
	assertIsReg("file", 0644);
	failure(msg);
	assertFileSize("file", 10);
	failure(msg);
	assertFileNLinks("file", 2);

	/* Another name for the same file. */
	failure(msg);
	assertIsHardlink("linkfile", "file");

	/* Symlink */
	if (canSymlink())
		assertIsSymlink("symlink", "file", 0);

	/* Another file with 1 link and different permissions. */
	failure(msg);
	assertIsReg("file2", 0777);
	failure(msg);
	assertFileSize("file2", 10);
	failure(msg);
	assertFileNLinks("file2", 1);

	/* dir */
	assertIsDir("dir", 0775);
}