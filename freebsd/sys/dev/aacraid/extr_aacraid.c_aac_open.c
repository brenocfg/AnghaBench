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
struct cdev {struct aac_softc* si_drv1; } ;
struct aac_softc {int /*<<< orphan*/  aac_dev; } ;

/* Variables and functions */
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  aac_cdevpriv_dtor ; 
 int /*<<< orphan*/  devfs_set_cdevpriv (struct aac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

__attribute__((used)) static int
aac_open(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct aac_softc *sc;

	sc = dev->si_drv1;
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");
#if __FreeBSD_version >= 702000
	device_busy(sc->aac_dev);
	devfs_set_cdevpriv(sc, aac_cdevpriv_dtor);
#endif
	return 0;
}