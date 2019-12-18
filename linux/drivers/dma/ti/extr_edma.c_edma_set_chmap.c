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
struct edma_chan {int ch_num; struct edma_cc* ecc; } ;
struct edma_cc {scalar_t__ chmap_exist; } ;

/* Variables and functions */
 int EDMA_CHAN_SLOT (int) ; 
 int /*<<< orphan*/  EDMA_DCHMAP ; 
 int /*<<< orphan*/  edma_write_array (struct edma_cc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void edma_set_chmap(struct edma_chan *echan, int slot)
{
	struct edma_cc *ecc = echan->ecc;
	int channel = EDMA_CHAN_SLOT(echan->ch_num);

	if (ecc->chmap_exist) {
		slot = EDMA_CHAN_SLOT(slot);
		edma_write_array(ecc, EDMA_DCHMAP, channel, (slot << 5));
	}
}