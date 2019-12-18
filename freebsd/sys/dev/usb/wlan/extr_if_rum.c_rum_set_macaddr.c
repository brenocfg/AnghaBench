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
struct rum_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT2573_MAC_CSR2 ; 
 int /*<<< orphan*/  RT2573_MAC_CSR3 ; 
 int /*<<< orphan*/  rum_write (struct rum_softc*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void
rum_set_macaddr(struct rum_softc *sc, const uint8_t *addr)
{

	rum_write(sc, RT2573_MAC_CSR2,
	    addr[0] | addr[1] << 8 | addr[2] << 16 | addr[3] << 24);
	rum_write(sc, RT2573_MAC_CSR3,
	    addr[4] | addr[5] << 8 | 0xff << 16);
}