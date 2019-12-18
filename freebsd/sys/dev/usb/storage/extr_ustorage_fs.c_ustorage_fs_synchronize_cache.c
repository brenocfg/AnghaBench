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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {struct ustorage_fs_lun* currlun; } ;
struct ustorage_fs_softc {TYPE_1__ sc_transfer; } ;
struct ustorage_fs_lun {int /*<<< orphan*/  sense_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SS_WRITE_ERROR ; 

__attribute__((used)) static uint8_t
ustorage_fs_synchronize_cache(struct ustorage_fs_softc *sc)
{
#if 0
	struct ustorage_fs_lun *currlun = sc->sc_transfer.currlun;
	uint8_t rc;

	/*
	 * We ignore the requested LBA and write out all dirty data buffers.
	 */
	rc = 0;
	if (rc) {
		currlun->sense_data = SS_WRITE_ERROR;
	}
#endif
	return (0);
}