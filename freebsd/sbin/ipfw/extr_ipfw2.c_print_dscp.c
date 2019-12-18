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
typedef  int uint32_t ;
struct buf_pr {int dummy; } ;
struct TYPE_3__ {int* d; } ;
typedef  TYPE_1__ ipfw_insn_u32 ;

/* Variables and functions */
 int /*<<< orphan*/  bprintf (struct buf_pr*,char*,...) ; 
 int /*<<< orphan*/  f_ipdscp ; 
 char* match_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
print_dscp(struct buf_pr *bp, ipfw_insn_u32 *cmd)
{
	int i = 0;
	uint32_t *v;
	char sep= ' ';
	const char *code;

	bprintf(bp, " dscp");
	v = cmd->d;
	while (i < 64) {
		if (*v & (1 << i)) {
			if ((code = match_value(f_ipdscp, i)) != NULL)
				bprintf(bp, "%c%s", sep, code);
			else
				bprintf(bp, "%c%d", sep, i);
			sep = ',';
		}

		if ((++i % 32) == 0)
			v++;
	}
}