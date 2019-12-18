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
typedef  int /*<<< orphan*/  uint8_t ;
struct ucycom_softc {int /*<<< orphan*/  sc_cfg; } ;
struct ucom_softc {struct ucycom_softc* sc_parent; } ;
struct termios {int c_cflag; int /*<<< orphan*/  c_ospeed; } ;

/* Variables and functions */
 int CIGNORE ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  UCYCOM_CFG_PAREN ; 
 int /*<<< orphan*/  UCYCOM_CFG_PARODD ; 
 int /*<<< orphan*/  UCYCOM_CFG_STOPB ; 
 int /*<<< orphan*/  ucycom_cfg_write (struct ucycom_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ucycom_cfg_param(struct ucom_softc *ucom, struct termios *t)
{
	struct ucycom_softc *sc = ucom->sc_parent;
	uint8_t cfg;

	DPRINTF("\n");

	if (t->c_cflag & CIGNORE) {
		cfg = sc->sc_cfg;
	} else {
		cfg = 0;
		switch (t->c_cflag & CSIZE) {
		default:
		case CS8:
			++cfg;
		case CS7:
			++cfg;
		case CS6:
			++cfg;
		case CS5:
			break;
		}

		if (t->c_cflag & CSTOPB)
			cfg |= UCYCOM_CFG_STOPB;
		if (t->c_cflag & PARENB)
			cfg |= UCYCOM_CFG_PAREN;
		if (t->c_cflag & PARODD)
			cfg |= UCYCOM_CFG_PARODD;
	}

	ucycom_cfg_write(sc, t->c_ospeed, cfg);
}