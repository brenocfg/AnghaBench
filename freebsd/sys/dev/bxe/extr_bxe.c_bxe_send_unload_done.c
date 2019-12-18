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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXE_NOMCP (struct bxe_softc*) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_DONE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_SKIP_LINK_RESET ; 
 int /*<<< orphan*/  bxe_fw_command (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_send_unload_done(struct bxe_softc *sc,
                     uint8_t          keep_link)
{
    uint32_t reset_param =
        keep_link ? DRV_MSG_CODE_UNLOAD_SKIP_LINK_RESET : 0;

    /* Report UNLOAD_DONE to MCP */
    if (!BXE_NOMCP(sc)) {
        bxe_fw_command(sc, DRV_MSG_CODE_UNLOAD_DONE, reset_param);
    }
}