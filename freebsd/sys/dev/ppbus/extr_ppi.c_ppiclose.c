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
struct ppi_data {int /*<<< orphan*/  ppi_lock; int /*<<< orphan*/  ppi_flags; int /*<<< orphan*/  ppi_device; } ;
struct cdev {struct ppi_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HAVE_PPBUS ; 
#define  PPB_ECP_FORWARD_IDLE 131 
#define  PPB_EPP_IDLE 130 
#define  PPB_PERIPHERAL_IDLE 129 
#define  PPB_REVERSE_IDLE 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int ppb_1284_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_1284_terminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_peripheral_terminate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ppiclose(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct ppi_data *ppi = dev->si_drv1;
	device_t ppidev = ppi->ppi_device;
	device_t ppbus = device_get_parent(ppidev);

	sx_xlock(&ppi->ppi_lock);
	ppb_lock(ppbus);
#ifdef PERIPH_1284
	switch (ppb_1284_get_state(ppbus)) {
	case PPB_PERIPHERAL_IDLE:
		ppb_peripheral_terminate(ppbus, 0);
		break;
	case PPB_REVERSE_IDLE:
	case PPB_EPP_IDLE:
	case PPB_ECP_FORWARD_IDLE:
	default:
		ppb_1284_terminate(ppbus);
		break;
	}
#endif /* PERIPH_1284 */

	/* unregistration of interrupt forced by release */
	ppb_release_bus(ppbus, ppidev);
	ppb_unlock(ppbus);

	ppi->ppi_flags &= ~HAVE_PPBUS;
	sx_xunlock(&ppi->ppi_lock);

	return (0);
}