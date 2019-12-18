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
struct fm801_info {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  FM_CODEC_CMD ; 
 int FM_CODEC_CMD_BUSY ; 
 int FM_CODEC_CMD_READ ; 
 int FM_CODEC_CMD_VALID ; 
 int /*<<< orphan*/  FM_CODEC_DATA ; 
 int TIMO ; 
 int fm801_rd (struct fm801_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm801_wr (struct fm801_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
fm801_rdcd(kobj_t obj, void *devinfo, int regno)
{
	struct fm801_info *fm801 = (struct fm801_info *)devinfo;
	int i;

	for (i = 0; i < TIMO && fm801_rd(fm801,FM_CODEC_CMD,2) & FM_CODEC_CMD_BUSY; i++) {
		DELAY(10000);
		DPRINT("fm801 rdcd: 1 - DELAY\n");
	}
	if (i >= TIMO) {
		printf("fm801 rdcd: codec busy\n");
		return 0;
	}

	fm801_wr(fm801,FM_CODEC_CMD, regno|FM_CODEC_CMD_READ,2);

	for (i = 0; i < TIMO && !(fm801_rd(fm801,FM_CODEC_CMD,2) & FM_CODEC_CMD_VALID); i++)
	{
		DELAY(10000);
		DPRINT("fm801 rdcd: 2 - DELAY\n");
	}
	if (i >= TIMO) {
		printf("fm801 rdcd: write codec invalid\n");
		return 0;
	}

	return fm801_rd(fm801,FM_CODEC_DATA,2);
}