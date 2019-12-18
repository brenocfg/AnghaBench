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
struct packet_command {unsigned int* cmd; int buflen; int /*<<< orphan*/  data_direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_READ ; 
 unsigned int GPCMD_REPORT_KEY ; 

__attribute__((used)) static void setup_report_key(struct packet_command *cgc, unsigned agid, unsigned type)
{
	cgc->cmd[0] = GPCMD_REPORT_KEY;
	cgc->cmd[10] = type | (agid << 6);
	switch (type) {
		case 0: case 8: case 5: {
			cgc->buflen = 8;
			break;
		}
		case 1: {
			cgc->buflen = 16;
			break;
		}
		case 2: case 4: {
			cgc->buflen = 12;
			break;
		}
	}
	cgc->cmd[9] = cgc->buflen;
	cgc->data_direction = CGC_DATA_READ;
}