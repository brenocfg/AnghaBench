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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct vmctx {int dummy; } ;
struct atkbdc_softc {int curcmd; int ctrlbyte; int status; int* ram; int outport; int /*<<< orphan*/  mtx; int /*<<< orphan*/  ps2kbd_sc; int /*<<< orphan*/  ps2mouse_sc; } ;

/* Variables and functions */
#define  KBDC_SET_COMMAND_BYTE 132 
#define  KBDC_WRITE_AUX_OUTBUF 131 
#define  KBDC_WRITE_KBD_OUTBUF 130 
#define  KBDC_WRITE_OUTPORT 129 
#define  KBDC_WRITE_TO_AUX 128 
 int KBDS_AUX_BUFFER_FULL ; 
 int KBDS_CTRL_FLAG ; 
 int KBDS_KBD_BUFFER_FULL ; 
 int KBDS_SYS_FLAG ; 
 int KBD_SYS_FLAG_BIT ; 
 int /*<<< orphan*/  atkbdc_aux_poll (struct atkbdc_softc*) ; 
 int /*<<< orphan*/  atkbdc_dequeue_data (struct atkbdc_softc*,int*) ; 
 int /*<<< orphan*/  atkbdc_kbd_queue_data (struct atkbdc_softc*,int) ; 
 int /*<<< orphan*/  atkbdc_poll (struct atkbdc_softc*) ; 
 int /*<<< orphan*/  ps2kbd_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ps2mouse_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
atkbdc_data_handler(struct vmctx *ctx, int vcpu, int in, int port, int bytes,
    uint32_t *eax, void *arg)
{
	struct atkbdc_softc *sc;
	uint8_t buf;
	int retval;

	if (bytes != 1)
		return (-1);
	sc = arg;
	retval = 0;

	pthread_mutex_lock(&sc->mtx);
	if (in) {
		sc->curcmd = 0;
		if (sc->ctrlbyte != 0) {
			*eax = sc->ctrlbyte & 0xff;
			sc->ctrlbyte = 0;
		} else {
			/* read device buffer; includes kbd cmd responses */
			atkbdc_dequeue_data(sc, &buf);
			*eax = buf;
		}

		sc->status &= ~KBDS_CTRL_FLAG;
		pthread_mutex_unlock(&sc->mtx);
		return (retval);
	}

	if (sc->status & KBDS_CTRL_FLAG) {
		/*
		 * Command byte for the controller.
		 */
		switch (sc->curcmd) {
		case KBDC_SET_COMMAND_BYTE:
			sc->ram[0] = *eax;
			if (sc->ram[0] & KBD_SYS_FLAG_BIT)
				sc->status |= KBDS_SYS_FLAG;
			else
				sc->status &= ~KBDS_SYS_FLAG;
			break;
		case KBDC_WRITE_OUTPORT:
			sc->outport = *eax;
			break;
		case KBDC_WRITE_TO_AUX:
			ps2mouse_write(sc->ps2mouse_sc, *eax, 0);
			atkbdc_poll(sc);
			break;
		case KBDC_WRITE_KBD_OUTBUF:
			atkbdc_kbd_queue_data(sc, *eax);
			break;
		case KBDC_WRITE_AUX_OUTBUF:
			ps2mouse_write(sc->ps2mouse_sc, *eax, 1);
			sc->status |= (KBDS_AUX_BUFFER_FULL | KBDS_KBD_BUFFER_FULL);
			atkbdc_aux_poll(sc);
			break;
		default:
			/* write to particular RAM byte */
			if (sc->curcmd >= 0x61 && sc->curcmd <= 0x7f) {
				int byten;

				byten = (sc->curcmd - 0x60) & 0x1f;
				sc->ram[byten] = *eax & 0xff;
			}
			break;
		}

		sc->curcmd = 0;
		sc->status &= ~KBDS_CTRL_FLAG;

		pthread_mutex_unlock(&sc->mtx);
		return (retval);
	}

	/*
	 * Data byte for the device.
	 */
	ps2kbd_write(sc->ps2kbd_sc, *eax);
	atkbdc_poll(sc);

	pthread_mutex_unlock(&sc->mtx);

	return (retval);
}