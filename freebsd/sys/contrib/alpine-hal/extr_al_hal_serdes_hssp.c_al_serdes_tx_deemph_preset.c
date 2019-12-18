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
struct al_serdes_grp_obj {int dummy; } ;
typedef  enum al_serdes_lane { ____Placeholder_al_serdes_lane } al_serdes_lane ;

/* Variables and functions */
 int /*<<< orphan*/  AL_SERDES_TX_DEEMPH_C_MINUS_PRESET ; 
 int /*<<< orphan*/  AL_SERDES_TX_DEEMPH_C_PLUS_PRESET ; 
 int /*<<< orphan*/  AL_SERDES_TX_DEEMPH_C_ZERO_PRESET ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_serdes_tx_deemph_set (struct al_serdes_grp_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void al_serdes_tx_deemph_preset(
		struct al_serdes_grp_obj	*obj,
		enum al_serdes_lane		lane)
{
	uint32_t c0;
	uint32_t c1;
	uint32_t c_1;

	c0 = AL_SERDES_TX_DEEMPH_C_ZERO_PRESET;

	c1 = AL_SERDES_TX_DEEMPH_C_PLUS_PRESET;

	c_1 = AL_SERDES_TX_DEEMPH_C_MINUS_PRESET;

	al_dbg("preset: new txdeemph: c0 = 0x%x c1 = 0x%x c-1 = 0x%x\n",
		c0, c1, c_1);

	al_serdes_tx_deemph_set(obj, lane, c0, c1, c_1);
}