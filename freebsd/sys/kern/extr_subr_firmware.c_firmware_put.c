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
struct priv_fw {scalar_t__ refcnt; scalar_t__ file; int /*<<< orphan*/  flags; TYPE_1__* parent; } ;
struct firmware {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int FIRMWARE_UNLOAD ; 
 int /*<<< orphan*/  FW_UNLOAD ; 
 struct priv_fw* PRIV_FW (struct firmware const*) ; 
 int /*<<< orphan*/  firmware_mtx ; 
 int /*<<< orphan*/  firmware_tq ; 
 int /*<<< orphan*/  firmware_unload_task ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
firmware_put(const struct firmware *p, int flags)
{
	struct priv_fw *fp = PRIV_FW(p);

	mtx_lock(&firmware_mtx);
	fp->refcnt--;
	if (fp->refcnt == 0) {
		if (fp->parent != NULL)
			fp->parent->refcnt--;
		if (flags & FIRMWARE_UNLOAD)
			fp->flags |= FW_UNLOAD;
		if (fp->file)
			taskqueue_enqueue(firmware_tq, &firmware_unload_task);
	}
	mtx_unlock(&firmware_mtx);
}