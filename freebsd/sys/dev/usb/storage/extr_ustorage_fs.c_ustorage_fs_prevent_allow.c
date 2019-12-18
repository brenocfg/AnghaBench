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
struct ustorage_fs_lun {int prevent_medium_removal; int /*<<< orphan*/  sense_data; int /*<<< orphan*/  removable; } ;
struct TYPE_3__ {int* CBWCDB; } ;

/* Variables and functions */
 int /*<<< orphan*/  SS_INVALID_COMMAND ; 
 int /*<<< orphan*/  SS_INVALID_FIELD_IN_CDB ; 

__attribute__((used)) static uint8_t
ustorage_fs_prevent_allow(struct ustorage_fs_softc *sc)
{
	struct ustorage_fs_lun *currlun = sc->sc_transfer.currlun;
	uint8_t prevent;

	if (!currlun->removable) {
		currlun->sense_data = SS_INVALID_COMMAND;
		return (1);
	}
	prevent = sc->sc_cbw->CBWCDB[4] & 0x01;
	if ((sc->sc_cbw->CBWCDB[4] & ~0x01) != 0) {
		/* Mask away Prevent */
		currlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		return (1);
	}
	if (currlun->prevent_medium_removal && !prevent) {
		//fsync_sub(currlun);
	}
	currlun->prevent_medium_removal = prevent;
	return (0);
}