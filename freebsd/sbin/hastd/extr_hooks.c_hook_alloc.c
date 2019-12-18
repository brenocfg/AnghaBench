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
struct hookproc {int /*<<< orphan*/  hp_magic; int /*<<< orphan*/  hp_comm; int /*<<< orphan*/  hp_lastreport; int /*<<< orphan*/  hp_birthtime; scalar_t__ hp_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOOKPROC_MAGIC_ALLOCATED ; 
 int /*<<< orphan*/  free (struct hookproc*) ; 
 struct hookproc* malloc (int) ; 
 int /*<<< orphan*/  pjdlog_error (char*,...) ; 
 int /*<<< orphan*/  snprlcat (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct hookproc *
hook_alloc(const char *path, char **args)
{
	struct hookproc *hp;
	unsigned int ii;

	hp = malloc(sizeof(*hp));
	if (hp == NULL) {
		pjdlog_error("Unable to allocate %zu bytes of memory for a hook.",
		    sizeof(*hp));
		return (NULL);
	}

	hp->hp_pid = 0;
	hp->hp_birthtime = hp->hp_lastreport = time(NULL);
	(void)strlcpy(hp->hp_comm, path, sizeof(hp->hp_comm));
	/* We start at 2nd argument as we don't want to have exec name twice. */
	for (ii = 1; args[ii] != NULL; ii++) {
		(void)snprlcat(hp->hp_comm, sizeof(hp->hp_comm), " %s",
		    args[ii]);
	}
	if (strlen(hp->hp_comm) >= sizeof(hp->hp_comm) - 1) {
		pjdlog_error("Exec path too long, correct configuration file.");
		free(hp);
		return (NULL);
	}
	hp->hp_magic = HOOKPROC_MAGIC_ALLOCATED;
	return (hp);
}