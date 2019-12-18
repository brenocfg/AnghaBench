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
typedef  int /*<<< orphan*/  u8 ;
struct si5351_driver_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int si5351_bulk_read(struct si5351_driver_data *drvdata,
				   u8 reg, u8 count, u8 *buf)
{
	return regmap_bulk_read(drvdata->regmap, reg, buf, count);
}