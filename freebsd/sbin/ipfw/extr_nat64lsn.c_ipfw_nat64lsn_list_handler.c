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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  NEED1 (char*) ; 
#define  TOK_CONFIG 129 
#define  TOK_STATES 128 
 int get_token (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  nat64listcmds ; 
 int /*<<< orphan*/  nat64lsn_foreach (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nat64lsn_show_cb ; 
 int /*<<< orphan*/  nat64lsn_states_cb ; 

__attribute__((used)) static void
ipfw_nat64lsn_list_handler(const char *name, uint8_t set, int ac, char *av[])
{
	int tcmd;

	if (ac == 0) {
		nat64lsn_foreach(nat64lsn_show_cb, name, set, 1);
		return;
	}
	NEED1("nat64lsn list needs command");
	tcmd = get_token(nat64listcmds, *av, "nat64lsn list command");
	switch (tcmd) {
	case TOK_STATES:
		nat64lsn_foreach(nat64lsn_states_cb, name, set, 1);
		break;
	case TOK_CONFIG:
		nat64lsn_foreach(nat64lsn_show_cb, name, set, 1);
	}
}