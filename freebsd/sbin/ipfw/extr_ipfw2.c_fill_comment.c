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
struct TYPE_3__ {int len; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ ipfw_insn ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CMDLEN ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int F_NOT ; 
 int F_OR ; 
 int /*<<< orphan*/  O_NOP ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
fill_comment(ipfw_insn *cmd, char **av, int cblen)
{
	int i, l;
	char *p = (char *)(cmd + 1);

	cmd->opcode = O_NOP;
	cmd->len =  (cmd->len & (F_NOT | F_OR));

	/* Compute length of comment string. */
	for (i = 0, l = 0; av[i] != NULL; i++)
		l += strlen(av[i]) + 1;
	if (l == 0)
		return;
	if (l > 84)
		errx(EX_DATAERR,
		    "comment too long (max 80 chars)");
	l = 1 + (l+3)/4;
	cmd->len =  (cmd->len & (F_NOT | F_OR)) | l;
	CHECK_CMDLEN;

	for (i = 0; av[i] != NULL; i++) {
		strcpy(p, av[i]);
		p += strlen(av[i]);
		*p++ = ' ';
	}
	*(--p) = '\0';
}