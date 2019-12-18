#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct buf_pr {int dummy; } ;
struct TYPE_3__ {int* d; } ;
typedef  TYPE_1__ ipfw_insn_u32 ;

/* Variables and functions */
 int /*<<< orphan*/  bprintf (struct buf_pr*,char*,...) ; 

void
print_icmp6types(struct buf_pr *bp, ipfw_insn_u32 *cmd)
{
	int i, j;
	char sep= ' ';

	bprintf(bp, " icmp6types");
	for (i = 0; i < 7; i++)
		for (j=0; j < 32; ++j) {
			if ( (cmd->d[i] & (1 << (j))) == 0)
				continue;
			bprintf(bp, "%c%d", sep, (i*32 + j));
			sep = ',';
		}
}