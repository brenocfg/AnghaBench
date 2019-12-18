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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct bsdtar {int /*<<< orphan*/ * filename; int /*<<< orphan*/ * names_from_file; int /*<<< orphan*/ ** argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ stat (int /*<<< orphan*/ *,struct stat*) ; 

__attribute__((used)) static void
test_for_append(struct bsdtar *bsdtar)
{
	struct stat s;

	if (*bsdtar->argv == NULL && bsdtar->names_from_file == NULL)
		lafe_errc(1, 0, "no files or directories specified");
	if (bsdtar->filename == NULL)
		lafe_errc(1, 0, "Cannot append to stdout.");

	if (stat(bsdtar->filename, &s) != 0)
		return;

	if (!S_ISREG(s.st_mode) && !S_ISBLK(s.st_mode))
		lafe_errc(1, 0,
		    "Cannot append to %s: not a regular file.",
		    bsdtar->filename);

/* Is this an appropriate check here on Windows? */
/*
	if (GetFileType(handle) != FILE_TYPE_DISK)
		lafe_errc(1, 0, "Cannot append");
*/

}