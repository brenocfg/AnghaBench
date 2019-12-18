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
typedef  int uint32_t ;
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dc_sbuf; } ;
struct dc_softc {TYPE_1__ dc_cdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int dc_mchash_le (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int) ; 

__attribute__((used)) static u_int
dc_hash_maddr_xircom(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct dc_softc *sc = arg;
	uint32_t h;

	h = dc_mchash_le(sc, LLADDR(sdl));
	sc->dc_cdata.dc_sbuf[h >> 4] |= htole32(1 << (h & 0xF));
	return (1);
}