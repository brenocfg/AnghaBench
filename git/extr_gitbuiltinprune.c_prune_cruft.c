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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  prune_tmp_file (char const*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int prune_cruft(const char *basename, const char *path, void *data)
{
	if (starts_with(basename, "tmp_obj_"))
		prune_tmp_file(path);
	else
		fprintf(stderr, "bad sha1 file: %s\n", path);
	return 0;
}