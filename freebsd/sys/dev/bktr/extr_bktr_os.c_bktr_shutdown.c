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
struct bktr_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_INTS_DISABLED ; 
 int /*<<< orphan*/  BKTR_GPIO_DMA_CTL ; 
 int /*<<< orphan*/  BKTR_INT_MASK ; 
 int /*<<< orphan*/  FIFO_RISC_DISABLED ; 
 int /*<<< orphan*/  OUTL (struct bktr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTW (struct bktr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bktr_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bktr_shutdown( device_t dev )
{
	struct bktr_softc *bktr = device_get_softc(dev);

	/* Disable the brooktree device */
	OUTL(bktr, BKTR_INT_MASK, ALL_INTS_DISABLED);
	OUTW(bktr, BKTR_GPIO_DMA_CTL, FIFO_RISC_DISABLED);

	return 0;
}