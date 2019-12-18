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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ use_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  NEED1 (char*) ; 
#define  TOK_CREATE 131 
#define  TOK_DESTROY 130 
#define  TOK_LIST 129 
 int TOK_RESET ; 
#define  TOK_STATS 128 
 TYPE_1__ co ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int get_token (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ nptv6_check_name (char const*) ; 
 int /*<<< orphan*/  nptv6_create (char const*,scalar_t__,int,char**) ; 
 int /*<<< orphan*/  nptv6_destroy (char const*,scalar_t__) ; 
 int /*<<< orphan*/  nptv6_destroy_cb ; 
 int /*<<< orphan*/  nptv6_foreach (int /*<<< orphan*/ ,char const*,scalar_t__,int) ; 
 int /*<<< orphan*/  nptv6_reset_stats (char const*,scalar_t__) ; 
 int /*<<< orphan*/  nptv6_show_cb ; 
 int /*<<< orphan*/  nptv6_stats (char const*,scalar_t__) ; 
 int /*<<< orphan*/  nptv6cmds ; 
 int /*<<< orphan*/  nptv6statscmds ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
ipfw_nptv6_handler(int ac, char *av[])
{
	const char *name;
	int tcmd;
	uint8_t set;

	if (co.use_set != 0)
		set = co.use_set - 1;
	else
		set = 0;
	ac--; av++;

	NEED1("nptv6 needs instance name");
	name = *av;
	if (nptv6_check_name(name) != 0) {
		if (strcmp(name, "all") == 0) {
			name = NULL;
		} else
			errx(EX_USAGE, "nptv6 instance name %s is invalid",
			    name);
	}
	ac--; av++;
	NEED1("nptv6 needs command");

	tcmd = get_token(nptv6cmds, *av, "nptv6 command");
	if (name == NULL && tcmd != TOK_DESTROY && tcmd != TOK_LIST)
		errx(EX_USAGE, "nptv6 instance name required");
	switch (tcmd) {
	case TOK_CREATE:
		ac--; av++;
		nptv6_create(name, set, ac, av);
		break;
	case TOK_LIST:
		nptv6_foreach(nptv6_show_cb, name, set, 1);
		break;
	case TOK_DESTROY:
		if (name == NULL)
			nptv6_foreach(nptv6_destroy_cb, NULL, set, 0);
		else
			nptv6_destroy(name, set);
		break;
	case TOK_STATS:
		ac--; av++;
		if (ac == 0) {
			nptv6_stats(name, set);
			break;
		}
		tcmd = get_token(nptv6statscmds, *av, "stats command");
		if (tcmd == TOK_RESET)
			nptv6_reset_stats(name, set);
	}
}