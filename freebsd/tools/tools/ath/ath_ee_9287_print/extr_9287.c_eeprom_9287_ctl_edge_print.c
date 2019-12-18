#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct cal_ctl_data_ar9287 {TYPE_1__** ctlEdges; } ;
struct TYPE_2__ {int tPowerFlag; } ;

/* Variables and functions */
 int AR9287_MAX_CHAINS ; 
 int AR9287_NUM_BAND_EDGES ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
eeprom_9287_ctl_edge_print(struct cal_ctl_data_ar9287 *ctl)
{
	int i, j;
	uint8_t pow, flag;

	for (i = 0; i < AR9287_MAX_CHAINS; i++) {
		printf("  chain %d: ", i);
		for (j = 0; j < AR9287_NUM_BAND_EDGES; j++) {
			pow = ctl->ctlEdges[i][j].tPowerFlag & 0x3f;
			flag = (ctl->ctlEdges[i][j].tPowerFlag & 0xc0) >> 6;
			printf(" %d:pow=%d,flag=%.2x", j, pow, flag);
		}
		printf("\n");
	}
}