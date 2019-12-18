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
struct jailparam {char* jp_name; int /*<<< orphan*/ * jp_value; } ;
struct cfjail {int dummy; } ;

/* Variables and functions */
 int JAIL_CREATE ; 
 int JAIL_DYING ; 
 int JAIL_UPDATE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  jail_note (struct cfjail const*,char*,char*,char*) ; 
 char* jailparam_export (struct jailparam*) ; 
 int jailparam_set (struct jailparam*,unsigned int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  quoted_print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
jailparam_set_note(const struct cfjail *j, struct jailparam *jp, unsigned njp,
    int flags)
{
	char *value;
	int jid;
	unsigned i;

	jid = jailparam_set(jp, njp, flags);
	if (verbose > 0) {
		jail_note(j, "jail_set(%s%s)",
		    (flags & (JAIL_CREATE | JAIL_UPDATE)) == JAIL_CREATE
		    ? "JAIL_CREATE" : "JAIL_UPDATE",
		    (flags & JAIL_DYING) ? " | JAIL_DYING" : "");
		for (i = 0; i < njp; i++) {
			printf(" %s", jp[i].jp_name);
			if (jp[i].jp_value == NULL)
				continue;
			putchar('=');
			value = jailparam_export(jp + i);
			if (value == NULL)
				err(1, "jailparam_export");
			quoted_print(stdout, value);
			free(value);
		}
		if (jid < 0)
			printf(": %s", strerror(errno));
		printf("\n");
	}
	return jid;
}