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
typedef  int uint32_t ;
struct vmctx {int dummy; } ;
struct TYPE_2__ {scalar_t__ bcnt; } ;
struct atkbdc_softc {int status; int curcmd; int ctrlbyte; int* ram; int outport; TYPE_1__ kbd; int /*<<< orphan*/  ps2mouse_sc; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int CTRL_CMD_FLAG ; 
 int /*<<< orphan*/  EALREADY ; 
#define  KBDC_DISABLE_AUX_PORT 143 
#define  KBDC_DISABLE_KBD_PORT 142 
#define  KBDC_ENABLE_AUX_PORT 141 
#define  KBDC_ENABLE_KBD_PORT 140 
#define  KBDC_GET_COMMAND_BYTE 139 
#define  KBDC_READ_INPORT 138 
#define  KBDC_READ_OUTPORT 137 
#define  KBDC_RESET 136 
#define  KBDC_SET_COMMAND_BYTE 135 
#define  KBDC_TEST_AUX_PORT 134 
#define  KBDC_TEST_CTRL 133 
#define  KBDC_TEST_KBD_PORT 132 
#define  KBDC_WRITE_AUX_OUTBUF 131 
#define  KBDC_WRITE_KBD_OUTBUF 130 
#define  KBDC_WRITE_OUTPORT 129 
#define  KBDC_WRITE_TO_AUX 128 
 int KBDS_AUX_BUFFER_FULL ; 
 int KBDS_CTRL_FLAG ; 
 int KBDS_KBD_BUFFER_FULL ; 
 int KBD_DISABLE_AUX_PORT ; 
 int KBD_DISABLE_KBD_PORT ; 
 int /*<<< orphan*/  VM_SUSPEND_RESET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atkbdc_assert_aux_intr (struct atkbdc_softc*) ; 
 int /*<<< orphan*/  atkbdc_assert_kbd_intr (struct atkbdc_softc*) ; 
 int /*<<< orphan*/  atkbdc_poll (struct atkbdc_softc*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ps2mouse_fifocnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps2mouse_toggle (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int vm_suspend (struct vmctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atkbdc_sts_ctl_handler(struct vmctx *ctx, int vcpu, int in, int port,
    int bytes, uint32_t *eax, void *arg)
{
	struct atkbdc_softc *sc;
	int	error, retval;

	if (bytes != 1)
		return (-1);

	sc = arg;
	retval = 0;

	pthread_mutex_lock(&sc->mtx);

	if (in) {
		/* read status register */
		*eax = sc->status;
		pthread_mutex_unlock(&sc->mtx);
		return (retval);
	}


	sc->curcmd = 0;
	sc->status |= KBDS_CTRL_FLAG;
	sc->ctrlbyte = 0;

	switch (*eax) {
	case KBDC_GET_COMMAND_BYTE:
		sc->ctrlbyte = CTRL_CMD_FLAG | sc->ram[0];
		break;
	case KBDC_TEST_CTRL:
		sc->ctrlbyte = CTRL_CMD_FLAG | 0x55;
		break;
	case KBDC_TEST_AUX_PORT:
	case KBDC_TEST_KBD_PORT:
		sc->ctrlbyte = CTRL_CMD_FLAG | 0;
		break;
	case KBDC_READ_INPORT:
		sc->ctrlbyte = CTRL_CMD_FLAG | 0;
		break;
	case KBDC_READ_OUTPORT:
		sc->ctrlbyte = CTRL_CMD_FLAG | sc->outport;
		break;
	case KBDC_SET_COMMAND_BYTE:
	case KBDC_WRITE_OUTPORT:
	case KBDC_WRITE_KBD_OUTBUF:
	case KBDC_WRITE_AUX_OUTBUF:
		sc->curcmd = *eax;
		break;
	case KBDC_DISABLE_KBD_PORT:
		sc->ram[0] |= KBD_DISABLE_KBD_PORT;
		break;
	case KBDC_ENABLE_KBD_PORT:
		sc->ram[0] &= ~KBD_DISABLE_KBD_PORT;
		if (sc->kbd.bcnt > 0)
			sc->status |= KBDS_KBD_BUFFER_FULL;
		atkbdc_poll(sc);
		break;
	case KBDC_WRITE_TO_AUX:
		sc->curcmd = *eax;
		break;
	case KBDC_DISABLE_AUX_PORT:
		sc->ram[0] |= KBD_DISABLE_AUX_PORT;
		ps2mouse_toggle(sc->ps2mouse_sc, 0);
		sc->status &= ~(KBDS_AUX_BUFFER_FULL | KBDS_KBD_BUFFER_FULL);
		sc->outport &= ~KBDS_AUX_BUFFER_FULL;
		break;
	case KBDC_ENABLE_AUX_PORT:
		sc->ram[0] &= ~KBD_DISABLE_AUX_PORT;
		ps2mouse_toggle(sc->ps2mouse_sc, 1);
		if (ps2mouse_fifocnt(sc->ps2mouse_sc) > 0)
			sc->status |= KBDS_AUX_BUFFER_FULL | KBDS_KBD_BUFFER_FULL;
		break;
	case KBDC_RESET:		/* Pulse "reset" line */
		error = vm_suspend(ctx, VM_SUSPEND_RESET);
		assert(error == 0 || errno == EALREADY);
		break;
	default:
		if (*eax >= 0x21 && *eax <= 0x3f) {
			/* read "byte N" from RAM */
			int	byten;

			byten = (*eax - 0x20) & 0x1f;
			sc->ctrlbyte = CTRL_CMD_FLAG | sc->ram[byten];
		}
		break;
	}

	pthread_mutex_unlock(&sc->mtx);

	if (sc->ctrlbyte != 0) {
		sc->status |= KBDS_KBD_BUFFER_FULL;
		sc->status &= ~KBDS_AUX_BUFFER_FULL;
		atkbdc_assert_kbd_intr(sc);
	} else if (ps2mouse_fifocnt(sc->ps2mouse_sc) > 0 &&
	           (sc->ram[0] & KBD_DISABLE_AUX_PORT) == 0) {
		sc->status |= KBDS_AUX_BUFFER_FULL | KBDS_KBD_BUFFER_FULL;
		atkbdc_assert_aux_intr(sc);
	} else if (sc->kbd.bcnt > 0 && (sc->ram[0] & KBD_DISABLE_KBD_PORT) == 0) {
		sc->status |= KBDS_KBD_BUFFER_FULL;
		atkbdc_assert_kbd_intr(sc);
	}

	return (retval);
}