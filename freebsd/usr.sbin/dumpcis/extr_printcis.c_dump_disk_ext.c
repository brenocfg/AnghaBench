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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_disk_ext(u_char *p, int len)
{
	if (len < 1)
		return;
	switch (p[0]) {
	case 1:			/* IDE interface */
		if (len < 2)
			goto err;
		printf("\tDisk interface: %s\n",
		       (p[1] & 1) ? "IDE" : "Undefined");
		break;
	case 2:			/* Master */
	case 3:			/* Slave */
		if (len < 3)
			goto err;
		printf("\tDisk features: %s, %s%s\n",
		       (p[1] & 0x04) ? "Silicon" : "Rotating",
		       (p[1] & 0x08) ? "Unique, " : "",
		       (p[1] & 0x10) ? "Dual" : "Single");
		if (p[2] & 0x7f)
			printf("\t\t%s%s%s%s%s%s%s\n",
			       (p[2] & 0x01) ? "Sleep, " : "",
			       (p[2] & 0x02) ? "Standby, " : "",
			       (p[2] & 0x04) ? "Idle, " : "",
			       (p[2] & 0x08) ? "Low power, " : "",
			       (p[2] & 0x10) ? "Reg inhibit, " : "",
			       (p[2] & 0x20) ? "Index, " : "",
			       (p[2] & 0x40) ? "Iois16" : "");
		break;
	err:	/* warning */
		printf("\tWrong length for fixed disk extension tuple\n");
		return;
	}
}