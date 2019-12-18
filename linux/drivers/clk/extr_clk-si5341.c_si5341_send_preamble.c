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
typedef  int u32 ;
struct clk_si5341 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI5341_DEVICE_REV ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  si5341_preamble ; 
 int si5341_write_multiple (struct clk_si5341*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si5341_send_preamble(struct clk_si5341 *data)
{
	int res;
	u32 revision;

	/* For revision 2 and up, the values are slightly different */
	res = regmap_read(data->regmap, SI5341_DEVICE_REV, &revision);
	if (res < 0)
		return res;

	/* Write "preamble" as specified by datasheet */
	res = regmap_write(data->regmap, 0xB24, revision < 2 ? 0xD8 : 0xC0);
	if (res < 0)
		return res;
	res = si5341_write_multiple(data,
		si5341_preamble, ARRAY_SIZE(si5341_preamble));
	if (res < 0)
		return res;

	/* Datasheet specifies a 300ms wait after sending the preamble */
	msleep(300);

	return 0;
}