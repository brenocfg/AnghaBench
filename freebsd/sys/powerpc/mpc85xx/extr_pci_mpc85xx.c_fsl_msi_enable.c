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
typedef  size_t u_int ;
struct fsl_msi_softc {struct fsl_msi_irq* sc_msi_irq; } ;
struct fsl_msi_irq {size_t* vectors; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t FSL_NUM_MSI_PER_IRQ ; 
 struct fsl_msi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fsl_msi_enable(device_t dev, u_int irq, u_int vector, void **priv)
{
	struct fsl_msi_softc *sc;
	struct fsl_msi_irq *irqd;

	sc = device_get_softc(dev);

	irqd = &sc->sc_msi_irq[irq / FSL_NUM_MSI_PER_IRQ];
	irqd->vectors[irq % FSL_NUM_MSI_PER_IRQ] = vector;
}