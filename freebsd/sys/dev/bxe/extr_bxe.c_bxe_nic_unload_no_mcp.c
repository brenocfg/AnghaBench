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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGI (struct bxe_softc*,char*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int FW_MSG_CODE_DRV_UNLOAD_COMMON ; 
 int FW_MSG_CODE_DRV_UNLOAD_FUNCTION ; 
 int FW_MSG_CODE_DRV_UNLOAD_PORT ; 
 int SC_PATH (struct bxe_softc*) ; 
 int SC_PORT (struct bxe_softc*) ; 
 scalar_t__** load_count ; 

__attribute__((used)) static int
bxe_nic_unload_no_mcp(struct bxe_softc *sc)
{
    int port = SC_PORT(sc);
    int path = SC_PATH(sc);

    BLOGI(sc, "NO MCP - load counts[%d]      %d, %d, %d\n",
          path, load_count[path][0], load_count[path][1],
          load_count[path][2]);
    load_count[path][0]--;
    load_count[path][1 + port]--;
    BLOGI(sc, "NO MCP - new load counts[%d]  %d, %d, %d\n",
          path, load_count[path][0], load_count[path][1],
          load_count[path][2]);
    if (load_count[path][0] == 0) {
        return (FW_MSG_CODE_DRV_UNLOAD_COMMON);
    } else if (load_count[path][1 + port] == 0) {
        return (FW_MSG_CODE_DRV_UNLOAD_PORT);
    } else {
        return (FW_MSG_CODE_DRV_UNLOAD_FUNCTION);
    }
}