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
typedef  int /*<<< orphan*/  u32 ;
struct edma_cc {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int EDMA_CHAN_SLOT (unsigned int) ; 
 scalar_t__ PARM_DST ; 
 int /*<<< orphan*/  PARM_OFFSET (unsigned int) ; 
 scalar_t__ PARM_SRC ; 
 int /*<<< orphan*/  edma_read (struct edma_cc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dma_addr_t edma_get_position(struct edma_cc *ecc, unsigned slot,
				    bool dst)
{
	u32 offs;

	slot = EDMA_CHAN_SLOT(slot);
	offs = PARM_OFFSET(slot);
	offs += dst ? PARM_DST : PARM_SRC;

	return edma_read(ecc, offs);
}