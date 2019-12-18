#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_2__ {int /*<<< orphan*/ * is_pic; } ;
struct msi_intsrc {TYPE_1__ msi_intsrc; scalar_t__ msi_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MSI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ first_msi_irq ; 
 int /*<<< orphan*/  intr_register_source (TYPE_1__*) ; 
 struct msi_intsrc* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ msi_last_irq ; 
 int /*<<< orphan*/  msi_lock ; 
 int /*<<< orphan*/  msi_pic ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nexus_add_irq (scalar_t__) ; 
 scalar_t__ num_msi_irqs ; 

__attribute__((used)) static void
msi_create_source(void)
{
	struct msi_intsrc *msi;
	u_int irq;

	mtx_lock(&msi_lock);
	if (msi_last_irq >= num_msi_irqs) {
		mtx_unlock(&msi_lock);
		return;
	}
	irq = msi_last_irq + first_msi_irq;
	msi_last_irq++;
	mtx_unlock(&msi_lock);

	msi = malloc(sizeof(struct msi_intsrc), M_MSI, M_WAITOK | M_ZERO);
	msi->msi_intsrc.is_pic = &msi_pic;
	msi->msi_irq = irq;
	intr_register_source(&msi->msi_intsrc);
	nexus_add_irq(irq);
}