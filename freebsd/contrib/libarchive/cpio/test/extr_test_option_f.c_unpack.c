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
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assertMakeDir (char const*,int) ; 
 int /*<<< orphan*/  extract_reference_file (char*) ; 
 int systemf (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  testprog ; 

__attribute__((used)) static void
unpack(const char *dirname, const char *option)
{
	int r;

	assertMakeDir(dirname, 0755);
	assertChdir(dirname);
	extract_reference_file("test_option_f.cpio");
	r = systemf("%s -i %s < test_option_f.cpio > copy-no-a.out 2>copy-no-a.err", testprog, option);
	assertEqualInt(0, r);
	assertChdir("..");
}