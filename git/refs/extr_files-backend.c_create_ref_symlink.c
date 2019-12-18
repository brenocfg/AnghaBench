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
struct ref_lock {int /*<<< orphan*/  lk; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_locked_file_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int symlink (char const*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int create_ref_symlink(struct ref_lock *lock, const char *target)
{
	int ret = -1;
#ifndef NO_SYMLINK_HEAD
	char *ref_path = get_locked_file_path(&lock->lk);
	unlink(ref_path);
	ret = symlink(target, ref_path);
	free(ref_path);

	if (ret)
		fprintf(stderr, "no symlink - falling back to symbolic ref\n");
#endif
	return ret;
}