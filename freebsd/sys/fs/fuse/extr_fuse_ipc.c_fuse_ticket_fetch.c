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
struct fuse_ticket {int dummy; } ;
struct fuse_data {int dataflags; int ticketer; } ;

/* Variables and functions */
 int FSESS_INITED ; 
 int /*<<< orphan*/  FUSE_LOCK () ; 
 int /*<<< orphan*/  FUSE_UNLOCK () ; 
 int PCATCH ; 
 int PDROP ; 
 int /*<<< orphan*/  fdata_set_dead (struct fuse_data*) ; 
 struct fuse_ticket* fticket_alloc (struct fuse_data*) ; 
 int /*<<< orphan*/  fuse_mtx ; 
 int msleep (int*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 

struct fuse_ticket *
fuse_ticket_fetch(struct fuse_data *data)
{
	int err = 0;
	struct fuse_ticket *ftick;

	ftick = fticket_alloc(data);

	if (!(data->dataflags & FSESS_INITED)) {
		/* Sleep until get answer for INIT messsage */
		FUSE_LOCK();
		if (!(data->dataflags & FSESS_INITED) && data->ticketer > 2) {
			err = msleep(&data->ticketer, &fuse_mtx, PCATCH | PDROP,
			    "fu_ini", 0);
			if (err)
				fdata_set_dead(data);
		} else
			FUSE_UNLOCK();
	}
	return ftick;
}