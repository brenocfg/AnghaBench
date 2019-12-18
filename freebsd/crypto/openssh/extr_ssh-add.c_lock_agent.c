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
typedef  int /*<<< orphan*/  prompt ;

/* Variables and functions */
 int /*<<< orphan*/  RP_ALLOW_STDIN ; 
 int /*<<< orphan*/  explicit_bzero (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* read_passphrase (char*,int /*<<< orphan*/ ) ; 
 char* ssh_err (int) ; 
 int ssh_lock_agent (int,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
lock_agent(int agent_fd, int lock)
{
	char prompt[100], *p1, *p2;
	int r, passok = 1, ret = -1;

	strlcpy(prompt, "Enter lock password: ", sizeof(prompt));
	p1 = read_passphrase(prompt, RP_ALLOW_STDIN);
	if (lock) {
		strlcpy(prompt, "Again: ", sizeof prompt);
		p2 = read_passphrase(prompt, RP_ALLOW_STDIN);
		if (strcmp(p1, p2) != 0) {
			fprintf(stderr, "Passwords do not match.\n");
			passok = 0;
		}
		explicit_bzero(p2, strlen(p2));
		free(p2);
	}
	if (passok) {
		if ((r = ssh_lock_agent(agent_fd, lock, p1)) == 0) {
			fprintf(stderr, "Agent %slocked.\n", lock ? "" : "un");
			ret = 0;
		} else {
			fprintf(stderr, "Failed to %slock agent: %s\n",
			    lock ? "" : "un", ssh_err(r));
		}
	}
	explicit_bzero(p1, strlen(p1));
	free(p1);
	return (ret);
}