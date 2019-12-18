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
struct passwd {char* pw_name; } ;
struct group {char* gr_name; } ;
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 int asprintf (char**,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 struct group* getgrgid (int /*<<< orphan*/ ) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 size_t strlen (char const*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  strtod (char const*,char**) ; 

__attribute__((used)) static char *
humanize_ids(char *rule)
{
	id_t id;
	struct passwd *pwd;
	struct group *grp;
	const char *subject, *textid, *rest;
	char *end, *humanized;
	int ret;

	subject = strsep(&rule, ":");
	textid = strsep(&rule, ":");
	if (textid == NULL)
		errx(1, "rule passed from the kernel didn't contain subject");
	if (rule != NULL)
		rest = rule;
	else
		rest = "";

	/* Replace numerical user and group ids with names. */
	if (strcasecmp(subject, "user") == 0) {
		id = strtod(textid, &end);
		if ((size_t)(end - textid) != strlen(textid))
			errx(1, "malformed uid '%s'", textid);
		pwd = getpwuid(id);
		if (pwd != NULL)
			textid = pwd->pw_name;
	} else if (strcasecmp(subject, "group") == 0) {
		id = strtod(textid, &end);
		if ((size_t)(end - textid) != strlen(textid))
			errx(1, "malformed gid '%s'", textid);
		grp = getgrgid(id);
		if (grp != NULL)
			textid = grp->gr_name;
	}

	ret = asprintf(&humanized, "%s:%s:%s", subject, textid, rest);
	if (ret <= 0)
		err(1, "asprintf");

	return (humanized);
}