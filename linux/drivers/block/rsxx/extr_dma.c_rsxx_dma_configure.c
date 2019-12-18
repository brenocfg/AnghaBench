#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  latency; int /*<<< orphan*/  count; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  stripe_size; TYPE_1__ intr_coal; } ;
struct TYPE_6__ {TYPE_2__ data; } ;
struct rsxx_cardinfo {TYPE_3__ config; scalar_t__ regmap; } ;

/* Variables and functions */
 scalar_t__ INTR_COAL ; 
 int /*<<< orphan*/  dma_intr_coal_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int rsxx_dma_stripe_setup (struct rsxx_cardinfo*,int /*<<< orphan*/ ) ; 

int rsxx_dma_configure(struct rsxx_cardinfo *card)
{
	u32 intr_coal;

	intr_coal = dma_intr_coal_val(card->config.data.intr_coal.mode,
				      card->config.data.intr_coal.count,
				      card->config.data.intr_coal.latency);
	iowrite32(intr_coal, card->regmap + INTR_COAL);

	return rsxx_dma_stripe_setup(card, card->config.data.stripe_size);
}