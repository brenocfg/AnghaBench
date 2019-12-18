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
struct clk_hw {int dummy; } ;
struct clk_audio_pad {int /*<<< orphan*/  regmap; int /*<<< orphan*/  div; int /*<<< orphan*/  qdaudio; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_AUDIO_PLL0 ; 
 int /*<<< orphan*/  AT91_PMC_AUDIO_PLL1 ; 
 int /*<<< orphan*/  AT91_PMC_AUDIO_PLL_PADEN ; 
 int /*<<< orphan*/  AT91_PMC_AUDIO_PLL_QDPAD_MASK ; 
 int /*<<< orphan*/  AUDIO_PLL_QDPAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_audio_pad* to_clk_audio_pad (struct clk_hw*) ; 

__attribute__((used)) static int clk_audio_pll_pad_enable(struct clk_hw *hw)
{
	struct clk_audio_pad *apad_ck = to_clk_audio_pad(hw);

	regmap_update_bits(apad_ck->regmap, AT91_PMC_AUDIO_PLL1,
			   AT91_PMC_AUDIO_PLL_QDPAD_MASK,
			   AUDIO_PLL_QDPAD(apad_ck->qdaudio, apad_ck->div));
	regmap_update_bits(apad_ck->regmap, AT91_PMC_AUDIO_PLL0,
			   AT91_PMC_AUDIO_PLL_PADEN, AT91_PMC_AUDIO_PLL_PADEN);

	return 0;
}