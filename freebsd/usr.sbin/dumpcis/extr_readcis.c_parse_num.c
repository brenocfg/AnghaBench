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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  tpl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpl24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpl32 (int /*<<< orphan*/ *) ; 

u_int
parse_num(int sz, u_char *p, u_char **q, int ofs)
{
	u_int num = 0;

	switch (sz) {	
	case 0:
	case 0x10:
		break;
	case 1:
	case 0x11:
		num = (*p++) + ofs;
		break;
	case 2:
	case 0x12:
		num = tpl16(p) + ofs;
		p += 2;
		break;
	case 0x13:
		num = tpl24(p) + ofs;
		p += 3;
		break;
	case 3:
	case 0x14:
		num = tpl32(p) + ofs;
		p += 4;
		break;
	}
	if (q)
		*q = p;
	return num;
}