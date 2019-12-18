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
typedef  int uint16_t ;
typedef  int u_int ;
struct xl_softc {int dummy; } ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_2 (struct xl_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int XL_CMD_RX_SET_HASH ; 
 int /*<<< orphan*/  XL_COMMAND ; 
 int XL_HASH_SET ; 
 int ether_crc32_be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
xl_check_maddr_90xB(void *arg, struct sockaddr_dl *sdl, u_int count)
{
	struct xl_softc *sc = arg;
	uint16_t h;

	h = ether_crc32_be(LLADDR(sdl), ETHER_ADDR_LEN) & 0xFF;
	CSR_WRITE_2(sc, XL_COMMAND, h | XL_CMD_RX_SET_HASH | XL_HASH_SET);

	return (1);
}