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
struct pcd_unit {int last_sense; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBMSG (char*) ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  pcd_atapi (struct pcd_unit*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcd_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcd_ready_wait(struct pcd_unit *cd, int tmo)
{
	char tr_cmd[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int k, p;

	k = 0;
	while (k < tmo) {
		cd->last_sense = 0;
		pcd_atapi(cd, tr_cmd, 0, NULL, DBMSG("test unit ready"));
		p = cd->last_sense;
		if (!p)
			return 0;
		if (!(((p & 0xffff) == 0x0402) || ((p & 0xff) == 6)))
			return p;
		k++;
		pcd_sleep(HZ);
	}
	return 0x000020;	/* timeout */
}