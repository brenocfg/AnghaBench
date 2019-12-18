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

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGB_DMAC_CMD ; 
 int /*<<< orphan*/  MGB_DMAC_RESET ; 
 int mgb_wait_for_bits (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mgb_dmac_reset(struct mgb_softc *sc)
{

	CSR_WRITE_REG(sc, MGB_DMAC_CMD, MGB_DMAC_RESET);
	return (mgb_wait_for_bits(sc, MGB_DMAC_CMD, 0, MGB_DMAC_RESET));
}