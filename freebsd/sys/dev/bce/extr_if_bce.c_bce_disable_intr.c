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
struct bce_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_PCICFG_INT_ACK_CMD ; 
 int /*<<< orphan*/  BCE_PCICFG_INT_ACK_CMD_MASK_INT ; 
 int /*<<< orphan*/  BCE_VERBOSE_INTR ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RD (struct bce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bce_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bce_disable_intr(struct bce_softc *sc)
{
	DBENTER(BCE_VERBOSE_INTR);

	REG_WR(sc, BCE_PCICFG_INT_ACK_CMD, BCE_PCICFG_INT_ACK_CMD_MASK_INT);
	REG_RD(sc, BCE_PCICFG_INT_ACK_CMD);

	DBEXIT(BCE_VERBOSE_INTR);
}