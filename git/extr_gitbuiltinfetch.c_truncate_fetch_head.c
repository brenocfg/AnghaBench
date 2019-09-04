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
 int /*<<< orphan*/  _ (char*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_for_writing (char const*) ; 
 char* git_path_fetch_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int truncate_fetch_head(void)
{
	const char *filename = git_path_fetch_head(the_repository);
	FILE *fp = fopen_for_writing(filename);

	if (!fp)
		return error_errno(_("cannot open %s"), filename);
	fclose(fp);
	return 0;
}