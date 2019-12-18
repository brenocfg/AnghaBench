#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct clk_si5341_synth {TYPE_1__* data; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI5341_SYNTH_N_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI5341_SYNTH_N_PIBYP ; 
 int /*<<< orphan*/  SI5341_SYNTH_N_UPD (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int si5341_encode_44_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si5341_synth_program(struct clk_si5341_synth *synth,
	u64 n_num, u32 n_den, bool is_integer)
{
	int err;
	u8 index = synth->index;

	err = si5341_encode_44_32(synth->data->regmap,
			SI5341_SYNTH_N_NUM(index), n_num, n_den);

	err = regmap_update_bits(synth->data->regmap,
		SI5341_SYNTH_N_PIBYP, BIT(index), is_integer ? BIT(index) : 0);
	if (err < 0)
		return err;

	return regmap_write(synth->data->regmap,
		SI5341_SYNTH_N_UPD(index), 0x01);
}