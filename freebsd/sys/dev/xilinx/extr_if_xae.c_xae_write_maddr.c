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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int u_int ;
struct xae_softc {int dummy; } ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int* LLADDR (struct sockaddr_dl*) ; 
 int READ4 (struct xae_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct xae_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XAE_FFC ; 
 int /*<<< orphan*/  XAE_FFV (int) ; 
 int XAE_MULTICAST_TABLE_SIZE ; 

__attribute__((used)) static u_int
xae_write_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct xae_softc *sc = arg;
	uint32_t reg;
	uint8_t *ma;

	if (cnt >= XAE_MULTICAST_TABLE_SIZE)
		return (1);

	ma = LLADDR(sdl);

	reg = READ4(sc, XAE_FFC) & 0xffffff00;
	reg |= cnt;
	WRITE4(sc, XAE_FFC, reg);

	reg = (ma[0]);
	reg |= (ma[1] << 8);
	reg |= (ma[2] << 16);
	reg |= (ma[3] << 24);
	WRITE4(sc, XAE_FFV(0), reg);

	reg = ma[4];
	reg |= ma[5] << 8;
	WRITE4(sc, XAE_FFV(1), reg);

	return (1);
}