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
struct mgb_softc {int dummy; } ;
struct ether_addr {int /*<<< orphan*/ * octet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_REG_BYTES (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MGB_MAC_ADDR_BASE_H ; 
 int /*<<< orphan*/  MGB_MAC_ADDR_BASE_L ; 

__attribute__((used)) static void
mgb_get_ethaddr(struct mgb_softc *sc, struct ether_addr *dest)
{

	CSR_READ_REG_BYTES(sc, MGB_MAC_ADDR_BASE_L, &dest->octet[0], 4);
	CSR_READ_REG_BYTES(sc, MGB_MAC_ADDR_BASE_H, &dest->octet[4], 2);
}