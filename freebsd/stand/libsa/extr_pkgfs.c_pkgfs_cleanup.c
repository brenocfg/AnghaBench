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
struct tarfile {scalar_t__ tf_cachesz; struct tarfile* pkg_chain; struct tarfile* tf_cache; struct tarfile* tf_next; struct tarfile* pkg_first; int /*<<< orphan*/  pkg_fd; int /*<<< orphan*/  pkg_zs; } ;
struct package {scalar_t__ tf_cachesz; struct package* pkg_chain; struct package* tf_cache; struct package* tf_next; struct package* pkg_first; int /*<<< orphan*/  pkg_fd; int /*<<< orphan*/  pkg_zs; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct tarfile*) ; 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 
 struct tarfile* package ; 

void
pkgfs_cleanup(void)
{
	struct package *chain;
	struct tarfile *tf, *tfn;

	while (package != NULL) {
		inflateEnd(&package->pkg_zs);
		close(package->pkg_fd);

		tf = package->pkg_first;
		while (tf != NULL) {
			tfn = tf->tf_next;
			if (tf->tf_cachesz > 0)
				free(tf->tf_cache);
			free(tf);
			tf = tfn;
		}

		chain = package->pkg_chain;
		free(package);
		package = chain;
	}
}