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
 int /*<<< orphan*/  bsd ; 
 int /*<<< orphan*/  category_file () ; 
 char* category_name () ; 
 int /*<<< orphan*/  dirname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mkdir (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

FILE *
open_category(void)
{
	FILE *file;

	if (verbose) {
		(void) printf("Writing category %s: ", category_name());
		(void) fflush(stdout);
	}

	/* make the parent directory */
	if (!bsd)
		(void) mkdir(dirname(category_file()), 0755);

	/*
	 * note that we have to regenerate the file name, as dirname
	 * clobbered it.
	 */
	file = fopen(category_file(), "w");
	if (file == NULL) {
		errf("%s", strerror(errno));
		return (NULL);
	}
	return (file);
}