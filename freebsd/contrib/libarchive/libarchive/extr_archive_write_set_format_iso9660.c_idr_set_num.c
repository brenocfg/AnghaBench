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
typedef  int /*<<< orphan*/  xdig ;

/* Variables and functions */

__attribute__((used)) static void
idr_set_num(unsigned char *p, int num)
{
	static const char xdig[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z'
	};

	num %= sizeof(xdig) * sizeof(xdig) * sizeof(xdig);
	p[0] = xdig[(num / (sizeof(xdig) * sizeof(xdig)))];
	num %= sizeof(xdig) * sizeof(xdig);
	p[1] = xdig[ (num / sizeof(xdig))];
	num %= sizeof(xdig);
	p[2] = xdig[num];
}