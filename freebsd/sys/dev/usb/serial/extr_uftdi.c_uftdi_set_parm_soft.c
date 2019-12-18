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
struct uftdi_softc {scalar_t__ sc_devtype; } ;
struct uftdi_param_config {int /*<<< orphan*/  v_flow; int /*<<< orphan*/  v_stop; int /*<<< orphan*/  v_start; int /*<<< orphan*/  lcr; } ;
struct ucom_softc {struct uftdi_softc* sc_parent; } ;
struct termios {int c_cflag; int c_iflag; int /*<<< orphan*/ * c_cc; int /*<<< orphan*/  c_ospeed; } ;

/* Variables and functions */
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 scalar_t__ DEVT_SIO ; 
 int /*<<< orphan*/  FTDI_SIO_DISABLE_FLOW_CTRL ; 
 int /*<<< orphan*/  FTDI_SIO_RTS_CTS_HS ; 
 int /*<<< orphan*/  FTDI_SIO_SET_DATA_BITS (int) ; 
 int /*<<< orphan*/  FTDI_SIO_SET_DATA_PARITY_EVEN ; 
 int /*<<< orphan*/  FTDI_SIO_SET_DATA_PARITY_NONE ; 
 int /*<<< orphan*/  FTDI_SIO_SET_DATA_PARITY_ODD ; 
 int /*<<< orphan*/  FTDI_SIO_SET_DATA_STOP_BITS_1 ; 
 int /*<<< orphan*/  FTDI_SIO_SET_DATA_STOP_BITS_2 ; 
 int /*<<< orphan*/  FTDI_SIO_XON_XOFF_HS ; 
 int IXOFF ; 
 int IXON ; 
 int PARENB ; 
 int PARODD ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  memset (struct uftdi_param_config*,int /*<<< orphan*/ ,int) ; 
 int uftdi_encode_baudrate (struct uftdi_softc*,int /*<<< orphan*/ ,struct uftdi_param_config*) ; 
 int uftdi_sio_encode_baudrate (struct uftdi_softc*,int /*<<< orphan*/ ,struct uftdi_param_config*) ; 

__attribute__((used)) static int
uftdi_set_parm_soft(struct ucom_softc *ucom, struct termios *t,
    struct uftdi_param_config *cfg)
{
	struct uftdi_softc *sc = ucom->sc_parent;
	int err;

	memset(cfg, 0, sizeof(*cfg));

	if (sc->sc_devtype == DEVT_SIO)
		err = uftdi_sio_encode_baudrate(sc, t->c_ospeed, cfg);
	else
		err = uftdi_encode_baudrate(sc, t->c_ospeed, cfg);
	if (err != 0)
		return (err);

	if (t->c_cflag & CSTOPB)
		cfg->lcr = FTDI_SIO_SET_DATA_STOP_BITS_2;
	else
		cfg->lcr = FTDI_SIO_SET_DATA_STOP_BITS_1;

	if (t->c_cflag & PARENB) {
		if (t->c_cflag & PARODD) {
			cfg->lcr |= FTDI_SIO_SET_DATA_PARITY_ODD;
		} else {
			cfg->lcr |= FTDI_SIO_SET_DATA_PARITY_EVEN;
		}
	} else {
		cfg->lcr |= FTDI_SIO_SET_DATA_PARITY_NONE;
	}

	switch (t->c_cflag & CSIZE) {
	case CS5:
		cfg->lcr |= FTDI_SIO_SET_DATA_BITS(5);
		break;

	case CS6:
		cfg->lcr |= FTDI_SIO_SET_DATA_BITS(6);
		break;

	case CS7:
		cfg->lcr |= FTDI_SIO_SET_DATA_BITS(7);
		break;

	case CS8:
		cfg->lcr |= FTDI_SIO_SET_DATA_BITS(8);
		break;
	}

	if (t->c_cflag & CRTSCTS) {
		cfg->v_flow = FTDI_SIO_RTS_CTS_HS;
	} else if (t->c_iflag & (IXON | IXOFF)) {
		cfg->v_flow = FTDI_SIO_XON_XOFF_HS;
		cfg->v_start = t->c_cc[VSTART];
		cfg->v_stop = t->c_cc[VSTOP];
	} else {
		cfg->v_flow = FTDI_SIO_DISABLE_FLOW_CTRL;
	}

	return (0);
}