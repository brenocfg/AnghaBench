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
struct tarfile {scalar_t__ tf_fp; scalar_t__ tf_size; scalar_t__ tf_cachesz; int /*<<< orphan*/  tf_cache; } ;
struct open_file {scalar_t__ f_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pkg_close(struct open_file *f)
{
	struct tarfile *tf;

	tf = (struct tarfile *)f->f_fsdata;
	if (tf == NULL)
		return (0);

	/*
	 * Free up the cache if we read all of the file.
	 */
	if (tf->tf_fp == tf->tf_size && tf->tf_cachesz > 0) {
		free(tf->tf_cache);
		tf->tf_cachesz = 0;
	}
	return (0);
}