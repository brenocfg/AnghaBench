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
struct lock_file {int dummy; } ;

/* Variables and functions */
 scalar_t__ commit_lock_file_to (struct lock_file*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_locked_file_path (struct lock_file*) ; 

int commit_lock_file(struct lock_file *lk)
{
	char *result_path = get_locked_file_path(lk);

	if (commit_lock_file_to(lk, result_path)) {
		int save_errno = errno;
		free(result_path);
		errno = save_errno;
		return -1;
	}
	free(result_path);
	return 0;
}