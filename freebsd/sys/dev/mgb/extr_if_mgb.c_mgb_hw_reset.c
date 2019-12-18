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
 int /*<<< orphan*/  CSR_UPDATE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGB_HW_CFG ; 
 int /*<<< orphan*/  MGB_LITE_RESET ; 
 int mgb_wait_for_bits (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mgb_hw_reset(struct mgb_softc *sc)
{

	CSR_UPDATE_REG(sc, MGB_HW_CFG, MGB_LITE_RESET);
	return (mgb_wait_for_bits(sc, MGB_HW_CFG, 0, MGB_LITE_RESET));
}