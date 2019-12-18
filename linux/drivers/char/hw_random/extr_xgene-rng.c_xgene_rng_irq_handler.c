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
struct xgene_rng_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  xgene_rng_chk_overflow (struct xgene_rng_dev*) ; 

__attribute__((used)) static irqreturn_t xgene_rng_irq_handler(int irq, void *id)
{
	struct xgene_rng_dev *ctx = (struct xgene_rng_dev *) id;

	/* RNG Alarm Counter overflow */
	xgene_rng_chk_overflow(ctx);

	return IRQ_HANDLED;
}