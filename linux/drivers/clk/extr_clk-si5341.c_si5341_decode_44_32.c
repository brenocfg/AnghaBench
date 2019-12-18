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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int get_unaligned_le32 (int*) ; 
 int regmap_bulk_read (struct regmap*,unsigned int,int*,int) ; 

__attribute__((used)) static int si5341_decode_44_32(struct regmap *regmap, unsigned int reg,
	u64 *val1, u32 *val2)
{
	int err;
	u8 r[10];

	err = regmap_bulk_read(regmap, reg, r, 10);
	if (err < 0)
		return err;

	*val1 = ((u64)((r[5] & 0x0f) << 8 | r[4]) << 32) |
		 (get_unaligned_le32(r));
	*val2 = get_unaligned_le32(&r[6]);

	return 0;
}