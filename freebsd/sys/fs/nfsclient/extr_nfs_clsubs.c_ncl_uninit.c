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
struct vfsconf {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ NFSIOD_AVAILABLE ; 
 int /*<<< orphan*/  NFSLOCKIOD () ; 
 int /*<<< orphan*/  NFSUNLOCKIOD () ; 
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncl_iod_mutex ; 
 scalar_t__ ncl_iodmax ; 
 scalar_t__* ncl_iodwant ; 
 int /*<<< orphan*/  ncl_nhuninit () ; 
 int ncl_numasync ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

int
ncl_uninit(struct vfsconf *vfsp)
{
	/*
	 * XXX: Unloading of nfscl module is unsupported.
	 */
#if 0
	int i;

	/*
	 * Tell all nfsiod processes to exit. Clear ncl_iodmax, and wakeup
	 * any sleeping nfsiods so they check ncl_iodmax and exit.
	 */
	NFSLOCKIOD();
	ncl_iodmax = 0;
	for (i = 0; i < ncl_numasync; i++)
		if (ncl_iodwant[i] == NFSIOD_AVAILABLE)
			wakeup(&ncl_iodwant[i]);
	/* The last nfsiod to exit will wake us up when ncl_numasync hits 0 */
	while (ncl_numasync)
		msleep(&ncl_numasync, &ncl_iod_mutex, PWAIT, "ioddie", 0);
	NFSUNLOCKIOD();
	ncl_nhuninit();
	return (0);
#else
	return (EOPNOTSUPP);
#endif
}