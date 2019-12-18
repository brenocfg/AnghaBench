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
struct passwd {int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _PATH_DEFPATH ; 
 int /*<<< orphan*/  _PATH_ETC_ENVIRONMENT ; 
 int asprintf (char**,char*,...) ; 
 scalar_t__ do_unique_tkfile ; 
 int read_environment (int /*<<< orphan*/ ,char***) ; 
 char** realloc (char**,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  syslog_and_die (char*) ; 
 int /*<<< orphan*/  tkfile ; 

__attribute__((used)) static void
setup_environment (char ***env, const struct passwd *pwd)
{
    int i, j, path;
    char **e;

    i = 0;
    path = 0;
    *env = NULL;

    i = read_environment(_PATH_ETC_ENVIRONMENT, env);
    e = *env;
    for (j = 0; j < i; j++) {
	if (!strncmp(e[j], "PATH=", 5)) {
	    path = 1;
	}
    }

    e = *env;
    e = realloc(e, (i + 7) * sizeof(char *));

    if (asprintf (&e[i++], "USER=%s",  pwd->pw_name) == -1)
	syslog_and_die ("asprintf: out of memory");
    if (asprintf (&e[i++], "HOME=%s",  pwd->pw_dir) == -1)
	syslog_and_die ("asprintf: out of memory");
    if (asprintf (&e[i++], "SHELL=%s", pwd->pw_shell) == -1)
	syslog_and_die ("asprintf: out of memory");
    if (! path) {
	if (asprintf (&e[i++], "PATH=%s",  _PATH_DEFPATH) == -1)
	    syslog_and_die ("asprintf: out of memory");
    }
    asprintf (&e[i++], "SSH_CLIENT=only_to_make_bash_happy");
    if (do_unique_tkfile)
	if (asprintf (&e[i++], "KRB5CCNAME=%s", tkfile) == -1)
	    syslog_and_die ("asprintf: out of memory");
    e[i++] = NULL;
    *env = e;
}