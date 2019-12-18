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
struct uio {int /*<<< orphan*/  uio_resid; } ;
struct ppi_data {int /*<<< orphan*/  ppi_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct ppb_microseq {TYPE_1__ member_1; int /*<<< orphan*/  member_0; } ;
struct cdev {struct ppi_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS ; 
 int /*<<< orphan*/  BUFSIZE ; 
 int ENODEV ; 
#define  EWOULDBLOCK 128 
 int /*<<< orphan*/  LENGTH ; 
 int /*<<< orphan*/  MS_OP_PUT ; 
 struct ppb_microseq MS_RET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_UNKNOWN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PCATCH ; 
 int PPBPRI ; 
 int /*<<< orphan*/  PPB_BYTE ; 
 int /*<<< orphan*/  PPB_ECP ; 
 scalar_t__ PPB_PERIPHERAL_IDLE ; 
 scalar_t__ PPB_PERIPHERAL_NEGOCIATION ; 
 int byte_peripheral_write (int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ppb_1284_get_state (int /*<<< orphan*/ ) ; 
 scalar_t__ ppb_1284_negociate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_1284_terminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_MS_init_msq (struct ppb_microseq*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int ppb_MS_microseq (int /*<<< orphan*/ ,struct ppb_microseq*,int*) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_peripheral_negociate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ppb_sleep (int /*<<< orphan*/ ,struct ppi_data*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppi_enable_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  uiomove (char*,int,struct uio*) ; 

__attribute__((used)) static int
ppiwrite(struct cdev *dev, struct uio *uio, int ioflag)
{
#ifdef PERIPH_1284
	struct ppi_data *ppi = dev->si_drv1;
	device_t ppidev = ppi->ppi_device;
	device_t ppbus = device_get_parent(ppidev);
	int len, error = 0, sent;
	char *buffer;

#if 0
	int ret;

	#define ADDRESS		MS_PARAM(0, 0, MS_TYP_PTR)
	#define LENGTH		MS_PARAM(0, 1, MS_TYP_INT)

	struct ppb_microseq msq[] = {
		  { MS_OP_PUT, { MS_UNKNOWN, MS_UNKNOWN, MS_UNKNOWN } },
		  MS_RET(0)
	};

	buffer = malloc(BUFSIZE, M_DEVBUF, M_WAITOK);
	ppb_lock(ppbus);

	/* negotiate ECP mode */
	if (ppb_1284_negociate(ppbus, PPB_ECP, 0)) {
		printf("ppiwrite: ECP negotiation failed\n");
	}

	while (!error && (len = min(uio->uio_resid, BUFSIZE))) {
		ppb_unlock(ppbus);
		uiomove(buffer, len, uio);

		ppb_MS_init_msq(msq, 2, ADDRESS, buffer, LENGTH, len);

		ppb_lock(ppbus);
		error = ppb_MS_microseq(ppbus, msq, &ret);
	}
#else
	buffer = malloc(BUFSIZE, M_DEVBUF, M_WAITOK);
	ppb_lock(ppbus);
#endif

	/* we have to be peripheral to be able to send data, so
	 * wait for the appropriate state
	 */
 	if (ppb_1284_get_state(ppbus) < PPB_PERIPHERAL_NEGOCIATION)
		ppb_1284_terminate(ppbus);

 	while (ppb_1284_get_state(ppbus) != PPB_PERIPHERAL_IDLE) {
		/* XXX should check a variable before sleeping */
#ifdef DEBUG_1284
		printf("s");
#endif

		ppi_enable_intr(ppidev);

		/* sleep until IEEE1284 negotiation starts */
		error = ppb_sleep(ppbus, ppi, PCATCH | PPBPRI, "ppiwrite", 0);

		switch (error) {
		case 0:
			/* negotiate peripheral side with BYTE mode */
			ppb_peripheral_negociate(ppbus, PPB_BYTE, 0);
			break;
		case EWOULDBLOCK:
			break;
		default:
			goto error;
		}
	}
#ifdef DEBUG_1284
	printf("N");
#endif

	/* negotiation done, write bytes to master host */
	while ((len = min(uio->uio_resid, BUFSIZE)) != 0) {
		ppb_unlock(ppbus);
		uiomove(buffer, len, uio);
		ppb_lock(ppbus);
		if ((error = byte_peripheral_write(ppbus,
						buffer, len, &sent)))
			goto error;
#ifdef DEBUG_1284
		printf("d");
#endif
	}

error:
	ppb_unlock(ppbus);
	free(buffer, M_DEVBUF);
#else /* PERIPH_1284 */
	int error = ENODEV;
#endif

	return (error);
}