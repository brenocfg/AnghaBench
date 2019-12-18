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
typedef  int /*<<< orphan*/  which ;
typedef  int /*<<< orphan*/  uint32_t ;
struct uath_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UATH_CMD_FLAG_MAGIC ; 
 int /*<<< orphan*/  WDCMSG_TARGET_GET_STATUS ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int uath_cmd_read (struct uath_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uath_get_status(struct uath_softc *sc, uint32_t which, void *odata, int olen)
{
	int error;

	which = htobe32(which);
	error = uath_cmd_read(sc, WDCMSG_TARGET_GET_STATUS,
	    &which, sizeof(which), odata, olen, UATH_CMD_FLAG_MAGIC);
	if (error != 0)
		device_printf(sc->sc_dev,
		    "could not read EEPROM offset 0x%02x\n", be32toh(which));
	return (error);
}