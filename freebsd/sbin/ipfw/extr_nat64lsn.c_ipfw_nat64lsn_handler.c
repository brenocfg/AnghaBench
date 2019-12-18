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
#define  TOK_STATS 128 
 TYPE_1__ co ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int get_token (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ipfw_nat64lsn_list_handler (char const*,scalar_t__,int,char**) ; 
 int /*<<< orphan*/  ipfw_nat64lsn_stats_handler (char const*,scalar_t__,int,char**) ; 
 int /*<<< orphan*/  nat64cmds ; 
 scalar_t__ nat64lsn_check_name (char const*) ; 
 int /*<<< orphan*/  nat64lsn_config (char const*,scalar_t__,int,char**) ; 
 int /*<<< orphan*/  nat64lsn_create (char const*,scalar_t__,int,char**) ; 
 int /*<<< orphan*/  nat64lsn_destroy (char const*,scalar_t__) ; 
 int /*<<< orphan*/  nat64lsn_destroy_cb ; 
 int /*<<< orphan*/  nat64lsn_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
ipfw_nat64lsn_handler(int ac, char *av[])
{
	const char *name;
	int tcmd;
	uint8_t set;

	if (co.use_set != 0)
		set = co.use_set - 1;
	else
		set = 0;
	ac--; av++;

	NEED1("nat64lsn needs instance name");
	name = *av;
	if (nat64lsn_check_name(name) != 0) {
		if (strcmp(name, "all") == 0)
			name = NULL;
		else
			errx(EX_USAGE, "nat64lsn instance name %s is invalid",
			    name);
	}
	ac--; av++;
	NEED1("nat64lsn needs command");

	tcmd = get_token(nat64cmds, *av, "nat64lsn command");
	if (name == NULL && tcmd != TOK_DESTROY && tcmd != TOK_LIST)
		errx(EX_USAGE, "nat64lsn instance name required");
	switch (tcmd) {
	case TOK_CREATE:
		ac--; av++;
		nat64lsn_create(name, set, ac, av);
		break;
	case TOK_CONFIG:
		ac--; av++;
		nat64lsn_config(name, set, ac, av);
		break;
	case TOK_LIST:
		ac--; av++;
		ipfw_nat64lsn_list_handler(name, set, ac, av);
		break;
	case TOK_DESTROY:
		if (name == NULL)
			nat64lsn_foreach(nat64lsn_destroy_cb, NULL, set, 0);
		else
			nat64lsn_destroy(name, set);
		break;
	case TOK_STATS:
		ac--; av++;
		ipfw_nat64lsn_stats_handler(name, set, ac, av);
	}
}