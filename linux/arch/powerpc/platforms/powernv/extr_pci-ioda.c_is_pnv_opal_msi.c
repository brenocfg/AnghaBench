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
struct irq_chip {scalar_t__ irq_eoi; } ;

/* Variables and functions */
 scalar_t__ pnv_ioda2_msi_eoi ; 

bool is_pnv_opal_msi(struct irq_chip *chip)
{
	return chip->irq_eoi == pnv_ioda2_msi_eoi;
}