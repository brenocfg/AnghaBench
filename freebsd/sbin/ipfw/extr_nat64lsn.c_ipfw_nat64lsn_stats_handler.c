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
#define  TOK_RESET 128 
 int get_token (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  nat64lsn_reset_stats (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nat64lsn_stats (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nat64statscmds ; 

__attribute__((used)) static void
ipfw_nat64lsn_stats_handler(const char *name, uint8_t set, int ac, char *av[])
{
	int tcmd;

	if (ac == 0) {
		nat64lsn_stats(name, set);
		return;
	}
	NEED1("nat64lsn stats needs command");
	tcmd = get_token(nat64statscmds, *av, "nat64lsn stats command");
	switch (tcmd) {
	case TOK_RESET:
		nat64lsn_reset_stats(name, set);
	}
}