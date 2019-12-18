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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertIsHardlink (char*,char*) ; 
 int /*<<< orphan*/  assertMakeDir (char*,int) ; 
 int /*<<< orphan*/  assertMakeHardlink (char*,char*) ; 
 int /*<<< orphan*/  assertMakeSymlink (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ canSymlink () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
make_files(void)
{
	FILE *f;

	/* File with 10 bytes content. */
	f = fopen("file", "wb");
	assert(f != NULL);
	assertEqualInt(10, fwrite("123456789", 1, 10, f));
	fclose(f);

	/* hardlink to above file. */
	assertMakeHardlink("linkfile", "file");
	assertIsHardlink("file", "linkfile");

	/* Symlink to above file. */
	if (canSymlink())
		assertMakeSymlink("symlink", "file", 0);

	/* Directory. */
	assertMakeDir("dir", 0775);

	return canSymlink()
	    ? "file linkfile symlink dir"
	    : "file linkfile dir";
}