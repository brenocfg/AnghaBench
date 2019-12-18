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
typedef  int /*<<< orphan*/  u_int32_t ;
struct mrsas_softc {int /*<<< orphan*/  pci_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  inbound_high_queue_port ; 
 int /*<<< orphan*/  inbound_low_queue_port ; 
 int /*<<< orphan*/  mrsas_reg_set ; 
 int /*<<< orphan*/  mrsas_write_reg (struct mrsas_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mrsas_write_64bit_req_desc(struct mrsas_softc *sc, u_int32_t req_desc_lo,
    u_int32_t req_desc_hi)
{
	mtx_lock(&sc->pci_lock);
	mrsas_write_reg(sc, offsetof(mrsas_reg_set, inbound_low_queue_port),
	    req_desc_lo);
	mrsas_write_reg(sc, offsetof(mrsas_reg_set, inbound_high_queue_port),
	    req_desc_hi);
	mtx_unlock(&sc->pci_lock);
}