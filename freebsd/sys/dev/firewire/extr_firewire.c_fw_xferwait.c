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
struct mtx {int dummy; } ;
struct fw_xfer {int flag; TYPE_1__* fc; } ;
struct TYPE_2__ {struct mtx wait_lock; } ;

/* Variables and functions */
 int FWXF_WAKE ; 
 int PCATCH ; 
 int PWAIT ; 
 int msleep (struct fw_xfer*,struct mtx*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 

int
fw_xferwait(struct fw_xfer *xfer)
{
	struct mtx *lock = &xfer->fc->wait_lock;
	int err = 0;

	mtx_lock(lock);
	while ((xfer->flag & FWXF_WAKE) == 0)
		err = msleep(xfer, lock, PWAIT|PCATCH, "fw_xferwait", 0);
	mtx_unlock(lock);

	return (err);
}