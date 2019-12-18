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
struct ipmi_softc {int /*<<< orphan*/  ipmi_opened; } ;
struct ipmi_device {struct ipmi_softc* ipmi_softc; int /*<<< orphan*/  ipmi_lun; int /*<<< orphan*/  ipmi_address; int /*<<< orphan*/  ipmi_completed_requests; } ;
struct cdev {struct ipmi_softc* si_drv1; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  IPMI_BMC_SLAVE_ADDR ; 
 int /*<<< orphan*/  IPMI_BMC_SMS_LUN ; 
 int /*<<< orphan*/  IPMI_LOCK (struct ipmi_softc*) ; 
 int /*<<< orphan*/  IPMI_UNLOCK (struct ipmi_softc*) ; 
 int /*<<< orphan*/  M_IPMI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int devfs_set_cdevpriv (struct ipmi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ipmi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_dtor ; 
 struct ipmi_device* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on ; 

__attribute__((used)) static int
ipmi_open(struct cdev *cdev, int flags, int fmt, struct thread *td)
{
	struct ipmi_device *dev;
	struct ipmi_softc *sc;
	int error;

	if (!on)
		return (ENOENT);

	/* Initialize the per file descriptor data. */
	dev = malloc(sizeof(struct ipmi_device), M_IPMI, M_WAITOK | M_ZERO);
	error = devfs_set_cdevpriv(dev, ipmi_dtor);
	if (error) {
		free(dev, M_IPMI);
		return (error);
	}

	sc = cdev->si_drv1;
	TAILQ_INIT(&dev->ipmi_completed_requests);
	dev->ipmi_address = IPMI_BMC_SLAVE_ADDR;
	dev->ipmi_lun = IPMI_BMC_SMS_LUN;
	dev->ipmi_softc = sc;
	IPMI_LOCK(sc);
	sc->ipmi_opened++;
	IPMI_UNLOCK(sc);

	return (0);
}