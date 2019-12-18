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
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;
struct priv_fw {scalar_t__ refcnt; int flags; int /*<<< orphan*/ * file; TYPE_1__ fw; } ;

/* Variables and functions */
 int FIRMWARE_MAX ; 
 int FW_UNLOAD ; 
 int /*<<< orphan*/  firmware_mtx ; 
 struct priv_fw* firmware_table ; 
 int linker_release_module (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
unloadentry(void *unused1, int unused2)
{
	int limit = FIRMWARE_MAX;
	int i;	/* current cycle */

	mtx_lock(&firmware_mtx);
	/*
	 * Scan the table. limit is set to make sure we make another
	 * full sweep after matching an entry that requires unloading.
	 */
	for (i = 0; i < limit; i++) {
		struct priv_fw *fp;
		int err;

		fp = &firmware_table[i % FIRMWARE_MAX];
		if (fp->fw.name == NULL || fp->file == NULL ||
		    fp->refcnt != 0 || (fp->flags & FW_UNLOAD) == 0)
			continue;

		/*
		 * Found an entry. Now:
		 * 1. bump up limit to make sure we make another full round;
		 * 2. clear FW_UNLOAD so we don't try this entry again.
		 * 3. release the lock while trying to unload the module.
		 * 'file' remains set so that the entry cannot be reused
		 * in the meantime (it also means that fp->file will
		 * not change while we release the lock).
		 */
		limit = i + FIRMWARE_MAX;	/* make another full round */
		fp->flags &= ~FW_UNLOAD;	/* do not try again */

		mtx_unlock(&firmware_mtx);
		err = linker_release_module(NULL, NULL, fp->file);
		mtx_lock(&firmware_mtx);

		/*
		 * We rely on the module to call firmware_unregister()
		 * on unload to actually release the entry.
		 * If err = 0 we can drop our reference as the system
		 * accepted it. Otherwise unloading failed (e.g. the
		 * module itself gave an error) so our reference is
		 * still valid.
		 */
		if (err == 0)
			fp->file = NULL; 
	}
	mtx_unlock(&firmware_mtx);
}