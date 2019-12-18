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
typedef  scalar_t__ uint8_t ;
struct bcma_intr {int i_mapped; scalar_t__ i_irq; scalar_t__ i_busline; scalar_t__ i_sel; scalar_t__ i_bank; } ;

/* Variables and functions */
 scalar_t__ BCMA_OOB_NUM_BANKS ; 
 scalar_t__ BCMA_OOB_NUM_BUSLINES ; 
 scalar_t__ BCMA_OOB_NUM_SEL ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct bcma_intr* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct bcma_intr *
bcma_alloc_intr(uint8_t bank, uint8_t sel, uint8_t line)
{
	struct bcma_intr *intr;

	if (bank >= BCMA_OOB_NUM_BANKS)
		return (NULL);

	if (sel >= BCMA_OOB_NUM_SEL)
		return (NULL);

	if (line >= BCMA_OOB_NUM_BUSLINES)
		return (NULL);

	intr = malloc(sizeof(*intr), M_BHND, M_NOWAIT);
	if (intr == NULL)
		return (NULL);

	intr->i_bank = bank;
	intr->i_sel = sel;
	intr->i_busline = line;
	intr->i_mapped = false;
	intr->i_irq = 0;

	return (intr);
}