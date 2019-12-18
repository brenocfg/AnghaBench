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
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int MCPR_NVM_ACCESS_ENABLE_EN ; 
 int MCPR_NVM_ACCESS_ENABLE_WR_EN ; 
 int /*<<< orphan*/  MCP_REG_MCPR_NVM_ACCESS_ENABLE ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bxe_disable_nvram_access(struct bxe_softc *sc)
{
    uint32_t val;

    val = REG_RD(sc, MCP_REG_MCPR_NVM_ACCESS_ENABLE);

    /* disable both bits, even after read */
    REG_WR(sc, MCP_REG_MCPR_NVM_ACCESS_ENABLE,
           (val & ~(MCPR_NVM_ACCESS_ENABLE_EN |
                    MCPR_NVM_ACCESS_ENABLE_WR_EN)));
}