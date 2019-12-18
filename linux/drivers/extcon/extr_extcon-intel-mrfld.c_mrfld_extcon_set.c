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
struct mrfld_extcon_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int mrfld_extcon_set(struct mrfld_extcon_data *data, unsigned int reg,
			    unsigned int mask)
{
	return regmap_update_bits(data->regmap, reg, mask, 0xff);
}