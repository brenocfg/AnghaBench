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
typedef  int /*<<< orphan*/  u_int ;
struct opalpci_softc {int /*<<< orphan*/  phb_id; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_PCI_MSI_EOI ; 
 int /*<<< orphan*/  PIC_ENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 struct opalpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  root_pic ; 

__attribute__((used)) static void
opalpic_pic_enable(device_t dev, u_int irq, u_int vector, void **priv)
{
	struct opalpci_softc *sc = device_get_softc(dev);

	PIC_ENABLE(root_pic, irq, vector, priv);
	opal_call(OPAL_PCI_MSI_EOI, sc->phb_id, irq, priv);
}