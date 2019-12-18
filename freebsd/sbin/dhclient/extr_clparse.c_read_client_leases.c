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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int LEASE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  new_parse (int /*<<< orphan*/ ) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_client_lease_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_dhclient_db ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (char*) ; 

void
read_client_leases(void)
{
	FILE	*cfile;
	char	*val;
	int	 token;

	new_parse(path_dhclient_db);

	/* Open the lease file.   If we can't open it, just return -
	   we can safely trust the server to remember our state. */
	if ((cfile = fopen(path_dhclient_db, "r")) == NULL)
		return;
	do {
		token = next_token(&val, cfile);
		if (token == EOF)
			break;
		if (token != LEASE) {
			warning("Corrupt lease file - possible data loss!");
			skip_to_semi(cfile);
			break;
		} else
			parse_client_lease_statement(cfile, 0);

	} while (1);
	fclose(cfile);
}