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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P3 (struct bxe_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 

__attribute__((used)) static void elink_save_spirom_version(struct bxe_softc *sc, uint8_t port,
				      uint32_t spirom_ver, uint32_t ver_addr)
{
	ELINK_DEBUG_P3(sc, "FW version 0x%x:0x%x for port %d\n",
		 (uint16_t)(spirom_ver>>16), (uint16_t)spirom_ver, port);

	if (ver_addr)
		REG_WR(sc, ver_addr, spirom_ver);
}