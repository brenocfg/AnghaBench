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
#define  TOK_CONFIG 132 
#define  TOK_CREATE 131 
#define  TOK_DESTROY 130 
#define  TOK_LIST 129 
 int TOK_RESET ; 
#define  TOK_STATS 128 
 TYPE_1__ co ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int get_token (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  nat64cmds ; 
 int /*<<< orphan*/  nat64statscmds ; 
 scalar_t__ nat64stl_check_name (char const*) ; 
 int /*<<< orphan*/  nat64stl_config (char const*,scalar_t__,int,char**) ; 
 int /*<<< orphan*/  nat64stl_create (char const*,scalar_t__,int,char**) ; 
 int /*<<< orphan*/  nat64stl_destroy (char const*,scalar_t__) ; 
 int /*<<< orphan*/  nat64stl_destroy_cb ; 
 int /*<<< orphan*/  nat64stl_foreach (int /*<<< orphan*/ ,char const*,scalar_t__,int) ; 
 int /*<<< orphan*/  nat64stl_reset_stats (char const*,scalar_t__) ; 
 int /*<<< orphan*/  nat64stl_show_cb ; 
 int /*<<< orphan*/  nat64stl_stats (char const*,scalar_t__) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
ipfw_nat64stl_handler(int ac, char *av[])
{
	const char *name;
	int tcmd;
	uint8_t set;

	if (co.use_set != 0)
		set = co.use_set - 1;
	else
		set = 0;
	ac--; av++;

	NEED1("nat64stl needs instance name");
	name = *av;
	if (nat64stl_check_name(name) != 0) {
		if (strcmp(name, "all") == 0)
			name = NULL;
		else
			errx(EX_USAGE, "nat64stl instance name %s is invalid",
			    name);
	}
	ac--; av++;
	NEED1("nat64stl needs command");

	tcmd = get_token(nat64cmds, *av, "nat64stl command");
	if (name == NULL && tcmd != TOK_DESTROY && tcmd != TOK_LIST)
		errx(EX_USAGE, "nat64stl instance name required");
	switch (tcmd) {
	case TOK_CREATE:
		ac--; av++;
		nat64stl_create(name, set, ac, av);
		break;
	case TOK_CONFIG:
		ac--; av++;
		nat64stl_config(name, set, ac, av);
		break;
	case TOK_LIST:
		nat64stl_foreach(nat64stl_show_cb, name, set, 1);
		break;
	case TOK_DESTROY:
		if (name == NULL)
			nat64stl_foreach(nat64stl_destroy_cb, NULL, set, 0);
		else
			nat64stl_destroy(name, set);
		break;
	case TOK_STATS:
		ac--; av++;
		if (ac == 0) {
			nat64stl_stats(name, set);
			break;
		}
		tcmd = get_token(nat64statscmds, *av, "stats command");
		if (tcmd == TOK_RESET)
			nat64stl_reset_stats(name, set);
	}
}