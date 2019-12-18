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
struct fd_info {int dupfd; scalar_t__ type; int fd; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int (* close ) (int) ;} ;

/* Variables and functions */
 int atomic_fetch_sub (int /*<<< orphan*/ *,int) ; 
 scalar_t__ fd_rsocket ; 
 int /*<<< orphan*/  free (struct fd_info*) ; 
 int /*<<< orphan*/  idm ; 
 int /*<<< orphan*/  idm_clear (int /*<<< orphan*/ *,int) ; 
 struct fd_info* idm_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_preload () ; 
 int rclose (int) ; 
 TYPE_1__ real ; 
 int stub1 (int) ; 
 int stub2 (int) ; 
 int stub3 (int) ; 

int close(int socket)
{
	struct fd_info *fdi;
	int ret;

	init_preload();
	fdi = idm_lookup(&idm, socket);
	if (!fdi)
		return real.close(socket);

	if (fdi->dupfd != -1) {
		ret = close(fdi->dupfd);
		if (ret)
			return ret;
	}

	if (atomic_fetch_sub(&fdi->refcnt, 1) != 1)
		return 0;

	idm_clear(&idm, socket);
	real.close(socket);
	ret = (fdi->type == fd_rsocket) ? rclose(fdi->fd) : real.close(fdi->fd);
	free(fdi);
	return ret;
}