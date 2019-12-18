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
typedef  int /*<<< orphan*/  uint32_t ;
struct ahci_channel {int /*<<< orphan*/  mtx; int /*<<< orphan*/  r_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_P_IS ; 
 int /*<<< orphan*/  ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_ch_intr_main (struct ahci_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ahci_ch_intr(void *arg)
{
	struct ahci_channel *ch = (struct ahci_channel *)arg;
	uint32_t istatus;

	/* Read interrupt statuses. */
	istatus = ATA_INL(ch->r_mem, AHCI_P_IS);

	mtx_lock(&ch->mtx);
	ahci_ch_intr_main(ch, istatus);
	mtx_unlock(&ch->mtx);
}