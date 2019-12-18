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
 int /*<<< orphan*/  assertTextFileContents (char*,char*) ; 
 int /*<<< orphan*/  failure (char*,int /*<<< orphan*/ ,...) ; 
 int systemf (char*,int /*<<< orphan*/ ,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  testprog ; 
 int /*<<< orphan*/  verify_files (char*) ; 

__attribute__((used)) static void
passthrough(const char *target)
{
	int r;

	if (!assertMakeDir(target, 0775))
		return;

	/*
	 * Use cpio passthrough mode to copy files to another directory.
	 */
	r = systemf("%s -p %s <filelist >%s/stdout 2>%s/stderr",
	    testprog, target, target, target);
	failure("Error invoking %s -p", testprog);
	assertEqualInt(r, 0);

	assertChdir(target);

	/* Verify stderr. */
	failure("Error invoking %s -p in dir %s",
	    testprog, target);
	assertTextFileContents("1 block\n", "stderr");

	verify_files("passthrough");
	assertChdir("..");
}