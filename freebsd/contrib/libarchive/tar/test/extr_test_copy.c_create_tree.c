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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertMakeDir (char*,int) ; 
 int /*<<< orphan*/  assertMakeFile (char*,int,char*) ; 
 int /*<<< orphan*/  assertMakeHardlink (char*,char*) ; 
 int /*<<< orphan*/  assertMakeSymlink (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ canSymlink () ; 
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  compute_filenames () ; 
 int compute_loop_max () ; 
 int /*<<< orphan*/  failure (char*,...) ; 
 char** filenames ; 
 int /*<<< orphan*/  skipping (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static void
create_tree(void)
{
	char buff[260];
	char buff2[260];
	int i;
	int LOOP_MAX;

	compute_filenames();

	/* Log that we'll be omitting some checks. */
	if (!canSymlink()) {
		skipping("Symlink checks");
	}

	assertMakeDir("original", 0775);
	assertEqualInt(0, chdir("original"));
	LOOP_MAX = compute_loop_max();

	assertMakeDir("f", 0775);
	assertMakeDir("l", 0775);
	assertMakeDir("m", 0775);
	assertMakeDir("s", 0775);
	assertMakeDir("d", 0775);

	for (i = 1; i < LOOP_MAX; i++) {
		failure("Internal sanity check failed: i = %d", i);
		assert(filenames[i] != NULL);

		sprintf(buff, "f/%s", filenames[i]);
		assertMakeFile(buff, 0777, buff);

		/* Create a link named "l/abcdef..." to the above. */
		sprintf(buff2, "l/%s", filenames[i]);
		assertMakeHardlink(buff2, buff);

		/* Create a link named "m/abcdef..." to the above. */
		sprintf(buff2, "m/%s", filenames[i]);
		assertMakeHardlink(buff2, buff);

		if (canSymlink()) {
			/* Create a symlink named "s/abcdef..." to the above. */
			sprintf(buff, "s/%s", filenames[i]);
			sprintf(buff2, "../f/%s", filenames[i]);
			failure("buff=\"%s\" buff2=\"%s\"", buff, buff2);
			assertMakeSymlink(buff, buff2, 0);
		}
		/* Create a dir named "d/abcdef...". */
		buff[0] = 'd';
		failure("buff=\"%s\"", buff);
		assertMakeDir(buff, 0775);
	}

	assertEqualInt(0, chdir(".."));
}