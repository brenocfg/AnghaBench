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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  bktr_ptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  TDA9887_ADDR ; 
 int /*<<< orphan*/  i2cWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
TDA9887_init(bktr_ptr_t bktr, int output2_enable)
{
	u_char addr = TDA9887_ADDR;

	i2cWrite(bktr, addr, 0, output2_enable ? 0x50 : 0xd0);
	i2cWrite(bktr, addr, 1, 0x6e); /* takeover point / de-emphasis */

	/* PAL BG: 0x09  PAL I: 0x0a  NTSC: 0x04 */
#ifdef MT2032_NTSC
	i2cWrite(bktr, addr, 2, 0x04);
#else
	i2cWrite(bktr, addr, 2, 0x09);
#endif
	return 0;
}