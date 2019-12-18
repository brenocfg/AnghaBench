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
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ shmem_base; } ;
struct TYPE_3__ {scalar_t__ shmem_base; } ;
struct bxe_softc {TYPE_2__ devinfo; TYPE_1__ link_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int MCP_ONE_TIMEOUT ; 
 int MCP_TIMEOUT ; 
 int /*<<< orphan*/  MISC_REG_SHARED_MEM_ADDR ; 
 scalar_t__ REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 size_t SC_PORT (struct bxe_softc*) ; 
 int SHMEM_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int SHR_MEM_VALIDITY_MB ; 
 int /*<<< orphan*/  bxe_mcp_wait_one (struct bxe_softc*) ; 
 int /*<<< orphan*/ * validity_map ; 

__attribute__((used)) static int
bxe_init_shmem(struct bxe_softc *sc)
{
    int cnt = 0;
    uint32_t val = 0;

    do {
        sc->devinfo.shmem_base     =
        sc->link_params.shmem_base =
            REG_RD(sc, MISC_REG_SHARED_MEM_ADDR);

        if (sc->devinfo.shmem_base) {
            val = SHMEM_RD(sc, validity_map[SC_PORT(sc)]);
            if (val & SHR_MEM_VALIDITY_MB)
                return (0);
        }

        bxe_mcp_wait_one(sc);

    } while (cnt++ < (MCP_TIMEOUT / MCP_ONE_TIMEOUT));

    BLOGE(sc, "BAD MCP validity signature\n");

    return (-1);
}