#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {struct ustorage_fs_lun* currlun; } ;
struct ustorage_fs_softc {TYPE_1__* sc_cbw; TYPE_2__ sc_transfer; } ;
struct ustorage_fs_lun {int /*<<< orphan*/  sense_data; int /*<<< orphan*/  removable; } ;
struct TYPE_3__ {int* CBWCDB; } ;

/* Variables and functions */
 int /*<<< orphan*/  SS_INVALID_COMMAND ; 

__attribute__((used)) static uint8_t
ustorage_fs_start_stop(struct ustorage_fs_softc *sc)
{
	struct ustorage_fs_lun *currlun = sc->sc_transfer.currlun;
	uint8_t loej;
	uint8_t start;
	uint8_t immed;

	if (!currlun->removable) {
		currlun->sense_data = SS_INVALID_COMMAND;
		return (1);
	}
	immed = sc->sc_cbw->CBWCDB[1] & 0x01;
	loej = sc->sc_cbw->CBWCDB[4] & 0x02;
	start = sc->sc_cbw->CBWCDB[4] & 0x01;

	if (immed || loej || start) {
		/* compile fix */
	}
	return (0);
}