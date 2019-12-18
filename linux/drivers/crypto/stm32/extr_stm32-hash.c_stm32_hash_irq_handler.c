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
typedef  int u32 ;
struct stm32_hash_dev {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FLAGS_OUTPUT_READY ; 
 int /*<<< orphan*/  HASH_IMR ; 
 int /*<<< orphan*/  HASH_SR ; 
 int HASH_SR_OUTPUT_READY ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int stm32_hash_read (struct stm32_hash_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_hash_write (struct stm32_hash_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t stm32_hash_irq_handler(int irq, void *dev_id)
{
	struct stm32_hash_dev *hdev = dev_id;
	u32 reg;

	reg = stm32_hash_read(hdev, HASH_SR);
	if (reg & HASH_SR_OUTPUT_READY) {
		reg &= ~HASH_SR_OUTPUT_READY;
		stm32_hash_write(hdev, HASH_SR, reg);
		hdev->flags |= HASH_FLAGS_OUTPUT_READY;
		/* Disable IT*/
		stm32_hash_write(hdev, HASH_IMR, 0);
		return IRQ_WAKE_THREAD;
	}

	return IRQ_NONE;
}