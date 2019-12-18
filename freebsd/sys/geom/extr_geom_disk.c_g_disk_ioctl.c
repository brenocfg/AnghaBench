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
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct g_provider {struct g_disk_softc* private; } ;
struct g_disk_softc {struct disk* dp; } ;
struct disk {int (* d_ioctl ) (struct disk*,int /*<<< orphan*/ ,void*,int,struct thread*) ;} ;

/* Variables and functions */
 int ENOIOCTL ; 
 int stub1 (struct disk*,int /*<<< orphan*/ ,void*,int,struct thread*) ; 

__attribute__((used)) static int
g_disk_ioctl(struct g_provider *pp, u_long cmd, void * data, int fflag, struct thread *td)
{
	struct disk *dp;
	struct g_disk_softc *sc;
	int error;

	sc = pp->private;
	dp = sc->dp;

	if (dp->d_ioctl == NULL)
		return (ENOIOCTL);
	error = dp->d_ioctl(dp, cmd, data, fflag, td);
	return (error);
}