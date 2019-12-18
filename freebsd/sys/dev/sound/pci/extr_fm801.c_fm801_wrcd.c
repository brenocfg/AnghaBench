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
typedef  int u_int32_t ;
struct fm801_info {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  FM_CODEC_CMD ; 
 int FM_CODEC_CMD_BUSY ; 
 int /*<<< orphan*/  FM_CODEC_DATA ; 
 int TIMO ; 
 int fm801_rd (struct fm801_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm801_wr (struct fm801_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
fm801_wrcd(kobj_t obj, void *devinfo, int regno, u_int32_t data)
{
	struct fm801_info *fm801 = (struct fm801_info *)devinfo;
	int i;

	DPRINT("fm801_wrcd reg 0x%x val 0x%x\n",regno, data);
/*
	if(regno == AC97_REG_RECSEL)	return;
*/
	/* Poll until codec is ready */
	for (i = 0; i < TIMO && fm801_rd(fm801,FM_CODEC_CMD,2) & FM_CODEC_CMD_BUSY; i++) {
		DELAY(10000);
		DPRINT("fm801 rdcd: 1 - DELAY\n");
	}
	if (i >= TIMO) {
		printf("fm801 wrcd: read codec busy\n");
		return -1;
	}

	fm801_wr(fm801,FM_CODEC_DATA,data, 2);
	fm801_wr(fm801,FM_CODEC_CMD, regno,2);

	/* wait until codec is ready */
	for (i = 0; i < TIMO && fm801_rd(fm801,FM_CODEC_CMD,2) & FM_CODEC_CMD_BUSY; i++) {
		DELAY(10000);
		DPRINT("fm801 wrcd: 2 - DELAY\n");
	}
	if (i >= TIMO) {
		printf("fm801 wrcd: read codec busy\n");
		return -1;
	}
	DPRINT("fm801 wrcd release reg 0x%x val 0x%x\n",regno, data);
	return 0;
}