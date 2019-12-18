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
struct rsxx_cardinfo {scalar_t__ ier_mask; scalar_t__ isr_mask; } ;

/* Variables and functions */

__attribute__((used)) static void rsxx_mask_interrupts(struct rsxx_cardinfo *card)
{
	card->isr_mask = 0;
	card->ier_mask = 0;
}