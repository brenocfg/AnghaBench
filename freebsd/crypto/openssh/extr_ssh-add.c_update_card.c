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
 int /*<<< orphan*/  RP_ALLOW_STDIN ; 
 int /*<<< orphan*/  confirm ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lifetime ; 
 char* read_passphrase (char*,int /*<<< orphan*/ ) ; 
 char* ssh_err (int) ; 
 int ssh_update_card (int,int,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
update_card(int agent_fd, int add, const char *id)
{
	char *pin = NULL;
	int r, ret = -1;

	if (add) {
		if ((pin = read_passphrase("Enter passphrase for PKCS#11: ",
		    RP_ALLOW_STDIN)) == NULL)
			return -1;
	}

	if ((r = ssh_update_card(agent_fd, add, id, pin == NULL ? "" : pin,
	    lifetime, confirm)) == 0) {
		fprintf(stderr, "Card %s: %s\n",
		    add ? "added" : "removed", id);
		ret = 0;
	} else {
		fprintf(stderr, "Could not %s card \"%s\": %s\n",
		    add ? "add" : "remove", id, ssh_err(r));
		ret = -1;
	}
	free(pin);
	return ret;
}