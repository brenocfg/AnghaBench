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

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  NEED1 (char*) ; 
#define  TOK_IFLIST 131 
#define  TOK_OLIST 130 
#define  TOK_TALIST 129 
#define  TOK_VLIST 128 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  intcmds ; 
 int /*<<< orphan*/  ipfw_list_objects (int,char**) ; 
 int /*<<< orphan*/  ipfw_list_ta (int,char**) ; 
 int /*<<< orphan*/  ipfw_list_tifaces () ; 
 int /*<<< orphan*/  ipfw_list_values (int,char**) ; 
 int match_token (int /*<<< orphan*/ ,char*) ; 

void
ipfw_internal_handler(int ac, char *av[])
{
	int tcmd;

	ac--; av++;
	NEED1("internal cmd required");

	if ((tcmd = match_token(intcmds, *av)) == -1)
		errx(EX_USAGE, "invalid internal sub-cmd: %s", *av);

	switch (tcmd) {
	case TOK_IFLIST:
		ipfw_list_tifaces();
		break;
	case TOK_TALIST:
		ipfw_list_ta(ac, av);
		break;
	case TOK_OLIST:
		ipfw_list_objects(ac, av);
		break;
	case TOK_VLIST:
		ipfw_list_values(ac, av);
		break;
	}
}