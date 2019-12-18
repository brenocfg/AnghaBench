#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ name; } ;
struct priv_fw {scalar_t__ refcnt; int /*<<< orphan*/  file; TYPE_1__ fw; } ;
typedef  int /*<<< orphan*/  linker_file_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  bzero (struct priv_fw*,int) ; 
 int /*<<< orphan*/  firmware_mtx ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 struct priv_fw* lookup (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
firmware_unregister(const char *imagename)
{
	struct priv_fw *fp;
	int err;

	mtx_lock(&firmware_mtx);
	fp = lookup(imagename, NULL);
	if (fp == NULL) {
		/*
		 * It is ok for the lookup to fail; this can happen
		 * when a module is unloaded on last reference and the
		 * module unload handler unregister's each of its
		 * firmware images.
		 */
		err = 0;
	} else if (fp->refcnt != 0) {	/* cannot unregister */
		err = EBUSY;
	} else {
		linker_file_t x = fp->file;	/* save value */

		/*
		 * Clear the whole entry with bzero to make sure we
		 * do not forget anything. Then restore 'file' which is
		 * non-null for autoloaded images.
		 */
		free((void *) (uintptr_t) fp->fw.name, M_TEMP);
		bzero(fp, sizeof(struct priv_fw));
		fp->file = x;
		err = 0;
	}
	mtx_unlock(&firmware_mtx);
	return err;
}