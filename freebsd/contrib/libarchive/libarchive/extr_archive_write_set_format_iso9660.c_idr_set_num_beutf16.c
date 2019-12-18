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
typedef  int uint16_t ;

/* Variables and functions */
 int XDIG_CNT ; 
 int /*<<< orphan*/  archive_be16enc (unsigned char*,int const) ; 

__attribute__((used)) static void
idr_set_num_beutf16(unsigned char *p, int num)
{
	static const uint16_t xdig[] = {
		0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035,
		0x0036, 0x0037, 0x0038, 0x0039,
		0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046,
		0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C,
		0x004D, 0x004E, 0x004F, 0x0050, 0x0051, 0x0052,
		0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058,
		0x0059, 0x005A
	};
#define XDIG_CNT	(sizeof(xdig)/sizeof(xdig[0]))

	num %= XDIG_CNT * XDIG_CNT * XDIG_CNT;
	archive_be16enc(p, xdig[(num / (XDIG_CNT * XDIG_CNT))]);
	num %= XDIG_CNT * XDIG_CNT;
	archive_be16enc(p+2, xdig[ (num / XDIG_CNT)]);
	num %= XDIG_CNT;
	archive_be16enc(p+4, xdig[num]);
}