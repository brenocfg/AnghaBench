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
struct TYPE_3__ {int len; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ ipfw_insn ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CMDLEN ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int F_INSN_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_DSCP ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  f_ipdscp ; 
 int /*<<< orphan*/  ipfw_insn_u32 ; 
 scalar_t__ isalpha (char) ; 
 int match_token (int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
fill_dscp(ipfw_insn *cmd, char *av, int cblen)
{
	uint32_t *low, *high;
	char *s = av, *a;
	int code;

	cmd->opcode = O_DSCP;
	cmd->len |= F_INSN_SIZE(ipfw_insn_u32) + 1;

	CHECK_CMDLEN;

	low = (uint32_t *)(cmd + 1);
	high = low + 1;

	*low = 0;
	*high = 0;

	while (s != NULL) {
		a = strchr(s, ',');

		if (a != NULL)
			*a++ = '\0';

		if (isalpha(*s)) {
			if ((code = match_token(f_ipdscp, s)) == -1)
				errx(EX_DATAERR, "Unknown DSCP code");
		} else {
			code = strtoul(s, NULL, 10);
			if (code < 0 || code > 63)
				errx(EX_DATAERR, "Invalid DSCP value");
		}

		if (code >= 32)
			*high |= 1 << (code - 32);
		else
			*low |= 1 << code;

		s = a;
	}
}