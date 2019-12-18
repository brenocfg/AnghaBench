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
struct thread {int dummy; } ;
struct iwn_stats {int dummy; } ;
struct iwn_softc {int /*<<< orphan*/  last_stat; } ;
struct iwn_ioctl_data {int /*<<< orphan*/  dst_addr; } ;
struct cdev {struct iwn_softc* si_drv1; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWN_LOCK (struct iwn_softc*) ; 
 int /*<<< orphan*/  IWN_UNLOCK (struct iwn_softc*) ; 
 int /*<<< orphan*/  PRIV_DRIVER ; 
#define  SIOCGIWNSTATS 129 
#define  SIOCZIWNSTATS 128 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwn_cdev_ioctl(struct cdev *dev, unsigned long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	int rc;
	struct iwn_softc *sc = dev->si_drv1;
	struct iwn_ioctl_data *d;

	rc = priv_check(td, PRIV_DRIVER);
	if (rc != 0)
		return (0);

	switch (cmd) {
	case SIOCGIWNSTATS:
		d = (struct iwn_ioctl_data *) data;
		IWN_LOCK(sc);
		/* XXX validate permissions/memory/etc? */
		rc = copyout(&sc->last_stat, d->dst_addr, sizeof(struct iwn_stats));
		IWN_UNLOCK(sc);
		break;
	case SIOCZIWNSTATS:
		IWN_LOCK(sc);
		memset(&sc->last_stat, 0, sizeof(struct iwn_stats));
		IWN_UNLOCK(sc);
		break;
	default:
		rc = EINVAL;
		break;
	}
	return (rc);
}