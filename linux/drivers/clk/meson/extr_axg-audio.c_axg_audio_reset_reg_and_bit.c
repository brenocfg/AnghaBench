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
struct axg_audio_reset_data {scalar_t__ offset; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 
 unsigned int regmap_get_reg_stride (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void axg_audio_reset_reg_and_bit(struct axg_audio_reset_data *rst,
					unsigned long id,
					unsigned int *reg,
					unsigned int *bit)
{
	unsigned int stride = regmap_get_reg_stride(rst->map);

	*reg = (id / (stride * BITS_PER_BYTE)) * stride;
	*reg += rst->offset;
	*bit = id % (stride * BITS_PER_BYTE);
}