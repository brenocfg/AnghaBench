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
typedef  int uint32_t ;
struct smc_softc {int /*<<< orphan*/  smc_intr; int /*<<< orphan*/  smc_tq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSR ; 
 int BSR_BANK_MASK ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  MSK ; 
 int smc_read_2 (struct smc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_select_bank (struct smc_softc*,int) ; 
 int /*<<< orphan*/  smc_write_1 (struct smc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smc_intr(void *context)
{
	struct smc_softc	*sc;
	uint32_t curbank;

	sc = (struct smc_softc *)context;

	/*
	 * Save current bank and restore later in this function
	 */
	curbank = (smc_read_2(sc, BSR) & BSR_BANK_MASK);

	/*
	 * Block interrupts in order to let smc_task_intr to kick in
	 */
	smc_select_bank(sc, 2);
	smc_write_1(sc, MSK, 0);

	/* Restore bank */
	smc_select_bank(sc, curbank);

	taskqueue_enqueue(sc->smc_tq, &sc->smc_intr);
	return (FILTER_HANDLED);
}