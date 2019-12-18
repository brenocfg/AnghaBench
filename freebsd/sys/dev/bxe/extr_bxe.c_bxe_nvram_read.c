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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int flash_size; } ;
struct bxe_softc {TYPE_1__ devinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int,int,...) ; 
 int MCPR_NVM_COMMAND_FIRST ; 
 int MCPR_NVM_COMMAND_LAST ; 
 int bxe_acquire_nvram_lock (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_disable_nvram_access (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_enable_nvram_access (struct bxe_softc*) ; 
 int bxe_nvram_read_dword (struct bxe_softc*,int,int*,int) ; 
 int /*<<< orphan*/  bxe_release_nvram_lock (struct bxe_softc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int
bxe_nvram_read(struct bxe_softc *sc,
               uint32_t         offset,
               uint8_t          *ret_buf,
               int              buf_size)
{
    uint32_t cmd_flags;
    uint32_t val;
    int rc;

    if ((offset & 0x03) || (buf_size & 0x03) || (buf_size == 0)) {
        BLOGE(sc, "Invalid parameter, offset 0x%x buf_size 0x%x\n",
              offset, buf_size);
        return (-1);
    }

    if ((offset + buf_size) > sc->devinfo.flash_size) {
        BLOGE(sc, "Invalid parameter, "
                  "offset 0x%x + buf_size 0x%x > flash_size 0x%x\n",
              offset, buf_size, sc->devinfo.flash_size);
        return (-1);
    }

    /* request access to nvram interface */
    rc = bxe_acquire_nvram_lock(sc);
    if (rc) {
        return (rc);
    }

    /* enable access to nvram interface */
    bxe_enable_nvram_access(sc);

    /* read the first word(s) */
    cmd_flags = MCPR_NVM_COMMAND_FIRST;
    while ((buf_size > sizeof(uint32_t)) && (rc == 0)) {
        rc = bxe_nvram_read_dword(sc, offset, &val, cmd_flags);
        memcpy(ret_buf, &val, 4);

        /* advance to the next dword */
        offset += sizeof(uint32_t);
        ret_buf += sizeof(uint32_t);
        buf_size -= sizeof(uint32_t);
        cmd_flags = 0;
    }

    if (rc == 0) {
        cmd_flags |= MCPR_NVM_COMMAND_LAST;
        rc = bxe_nvram_read_dword(sc, offset, &val, cmd_flags);
        memcpy(ret_buf, &val, 4);
    }

    /* disable access to nvram interface */
    bxe_disable_nvram_access(sc);
    bxe_release_nvram_lock(sc);

    return (rc);
}