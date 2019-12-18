#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bxe_softc {int /*<<< orphan*/  eeprom; } ;
struct TYPE_3__ {int eeprom_cmd; int /*<<< orphan*/  eeprom_data_len; int /*<<< orphan*/  eeprom_data; int /*<<< orphan*/  eeprom_offset; } ;
typedef  TYPE_1__ bxe_eeprom_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGW (struct bxe_softc*,char*,int,int) ; 
#define  BXE_EEPROM_CMD_GET_EEPROM 129 
#define  BXE_EEPROM_CMD_SET_EEPROM 128 
 int EINVAL ; 
 int bxe_rd_eeprom (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bxe_wr_eeprom (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_eeprom_rd_wr(struct bxe_softc *sc, bxe_eeprom_t *eeprom)
{
    int rval = 0;

    switch (eeprom->eeprom_cmd) {

    case BXE_EEPROM_CMD_SET_EEPROM:

        rval = copyin(eeprom->eeprom_data, sc->eeprom,
                       eeprom->eeprom_data_len);

        if (rval)
            break;

        rval = bxe_wr_eeprom(sc, sc->eeprom, eeprom->eeprom_offset,
                       eeprom->eeprom_data_len);
        break;

    case BXE_EEPROM_CMD_GET_EEPROM:

        rval = bxe_rd_eeprom(sc, sc->eeprom, eeprom->eeprom_offset,
                       eeprom->eeprom_data_len);

        if (rval) {
            break;
        }

        rval = copyout(sc->eeprom, eeprom->eeprom_data,
                       eeprom->eeprom_data_len);
        break;

    default:
            rval = EINVAL;
            break;
    }

    if (rval) {
        BLOGW(sc, "ioctl cmd %d  failed rval %d\n", eeprom->eeprom_cmd, rval);
    }

    return (rval);
}