#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xi ;
struct TYPE_4__ {int /*<<< orphan*/  mflags; int /*<<< orphan*/  limit; } ;
typedef  TYPE_1__ ipfw_xtable_info ;
typedef  int /*<<< orphan*/  ipfw_obj_header ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  IPFW_TMFLAGS_LIMIT ; 
 int /*<<< orphan*/  NEED1 (char*) ; 
#define  TOK_LIMIT 128 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int get_token (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ table_do_modify (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  tablenewcmds ; 

__attribute__((used)) static void
table_modify(ipfw_obj_header *oh, int ac, char *av[])
{
	ipfw_xtable_info xi;
	int tcmd;

	memset(&xi, 0, sizeof(xi));

	while (ac > 0) {
		tcmd = get_token(tablenewcmds, *av, "option");
		ac--; av++;

		switch (tcmd) {
		case TOK_LIMIT:
			NEED1("limit value required");
			xi.limit = strtol(*av, NULL, 10);
			xi.mflags |= IPFW_TMFLAGS_LIMIT;
			ac--; av++;
			break;
		default:
			errx(EX_USAGE, "cmd is not supported for modification");
		}
	}

	if (table_do_modify(oh, &xi) != 0)
		err(EX_OSERR, "Table modification failed");
}