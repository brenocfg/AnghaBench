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
typedef  int /*<<< orphan*/  uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_DONE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_SKIP_LINK_RESET ; 
 int /*<<< orphan*/  bxe_fw_command (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_prev_mcp_done(struct bxe_softc *sc)
{
    uint32_t rc = bxe_fw_command(sc, DRV_MSG_CODE_UNLOAD_DONE,
                                 DRV_MSG_CODE_UNLOAD_SKIP_LINK_RESET);
    if (!rc) {
        BLOGE(sc, "MCP response failure, aborting\n");
        return (-1);
    }

    return (0);
}