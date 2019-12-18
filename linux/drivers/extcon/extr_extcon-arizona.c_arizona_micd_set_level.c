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
struct arizona {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ARIZONA_MIC_DETECT_LEVEL_4 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 

__attribute__((used)) static void arizona_micd_set_level(struct arizona *arizona, int index,
				   unsigned int level)
{
	int reg;
	unsigned int mask;

	reg = ARIZONA_MIC_DETECT_LEVEL_4 - (index / 2);

	if (!(index % 2)) {
		mask = 0x3f00;
		level <<= 8;
	} else {
		mask = 0x3f;
	}

	/* Program the level itself */
	regmap_update_bits(arizona->regmap, reg, mask, level);
}