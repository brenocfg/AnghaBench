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
struct mvneta_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_MACAH ; 
 int /*<<< orphan*/  MVNETA_MACAL ; 
 int /*<<< orphan*/  MVNETA_WRITE (struct mvneta_softc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
mvneta_set_mac_address(struct mvneta_softc *sc, uint8_t *addr)
{
	unsigned int mac_h;
	unsigned int mac_l;

	mac_l = (addr[4] << 8) | (addr[5]);
	mac_h = (addr[0] << 24) | (addr[1] << 16) |
	    (addr[2] << 8) | (addr[3] << 0);

	MVNETA_WRITE(sc, MVNETA_MACAL, mac_l);
	MVNETA_WRITE(sc, MVNETA_MACAH, mac_h);
	return (0);
}