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
struct uio {scalar_t__ uio_resid; } ;
struct ppi_data {int /*<<< orphan*/  ppi_mode; int /*<<< orphan*/  ppi_device; } ;
struct cdev {struct ppi_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZE ; 
 int ENODEV ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PPBPRI ; 
 int /*<<< orphan*/  PPB_BYTE ; 
#define  PPB_ECP_FORWARD_IDLE 132 
#define  PPB_EPP_IDLE 131 
#define  PPB_FORWARD_IDLE 130 
 int /*<<< orphan*/  PPB_NIBBLE ; 
#define  PPB_PERIPHERAL_IDLE 129 
#define  PPB_REVERSE_IDLE 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int hz ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int ppb_1284_get_state (int /*<<< orphan*/ ) ; 
 int ppb_1284_negociate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ppb_1284_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_peripheral_terminate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_sleep (int /*<<< orphan*/ ,struct ppi_data*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int uiomove (char*,int,struct uio*) ; 

__attribute__((used)) static int
ppiread(struct cdev *dev, struct uio *uio, int ioflag)
{
#ifdef PERIPH_1284
	struct ppi_data *ppi = dev->si_drv1;
	device_t ppidev = ppi->ppi_device;
	device_t ppbus = device_get_parent(ppidev);
	int len, error = 0;
	char *buffer;

	buffer = malloc(BUFSIZE, M_DEVBUF, M_WAITOK);

	ppb_lock(ppbus);
	switch (ppb_1284_get_state(ppbus)) {
	case PPB_PERIPHERAL_IDLE:
		ppb_peripheral_terminate(ppbus, 0);
		/* FALLTHROUGH */

	case PPB_FORWARD_IDLE:
		/* if can't negotiate NIBBLE mode then try BYTE mode,
		 * the peripheral may be a computer
		 */
		if ((ppb_1284_negociate(ppbus,
			ppi->ppi_mode = PPB_NIBBLE, 0))) {

			/* XXX Wait 2 seconds to let the remote host some
			 * time to terminate its interrupt
			 */
			ppb_sleep(ppbus, ppi, PPBPRI, "ppiread", 2 * hz);

			if ((error = ppb_1284_negociate(ppbus,
			    ppi->ppi_mode = PPB_BYTE, 0))) {
				ppb_unlock(ppbus);
				free(buffer, M_DEVBUF);
				return (error);
			}
		}
		break;

	case PPB_REVERSE_IDLE:
	case PPB_EPP_IDLE:
	case PPB_ECP_FORWARD_IDLE:
	default:
		break;
	}

#ifdef DEBUG_1284
	printf("N");
#endif
	/* read data */
	len = 0;
	while (uio->uio_resid) {
		error = ppb_1284_read(ppbus, ppi->ppi_mode,
		    buffer, min(BUFSIZE, uio->uio_resid), &len);
		ppb_unlock(ppbus);
		if (error)
			goto error;

		if (!len)
			goto error;		/* no more data */

#ifdef DEBUG_1284
		printf("d");
#endif
		if ((error = uiomove(buffer, len, uio)))
			goto error;
		ppb_lock(ppbus);
	}
	ppb_unlock(ppbus);

error:
	free(buffer, M_DEVBUF);
#else /* PERIPH_1284 */
	int error = ENODEV;
#endif

	return (error);
}