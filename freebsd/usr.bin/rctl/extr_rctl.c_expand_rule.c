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
typedef  scalar_t__ id_t ;

/* Variables and functions */
 int asprintf (char**,char*,char const*,...) ; 
 char* expand_amount (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int parse_group (char const*,scalar_t__*,char const*) ; 
 int parse_user (char const*,scalar_t__*,char const*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static char *
expand_rule(const char *rule, bool resolve_ids)
{
	id_t id;
	const char *subject, *textid, *rest;
	char *copy, *expanded, *resolved, *tofree;
	int error, ret;

	tofree = copy = strdup(rule);
	if (copy == NULL) {
		warn("strdup");
		return (NULL);
	}

	subject = strsep(&copy, ":");
	textid = strsep(&copy, ":");
	if (textid == NULL) {
		warnx("malformed rule '%s': missing subject", rule);
		return (NULL);
	}
	if (copy != NULL)
		rest = copy;
	else
		rest = "";

	if (strcasecmp(subject, "u") == 0)
		subject = "user";
	else if (strcasecmp(subject, "g") == 0)
		subject = "group";
	else if (strcasecmp(subject, "p") == 0)
		subject = "process";
	else if (strcasecmp(subject, "l") == 0 ||
	    strcasecmp(subject, "c") == 0 ||
	    strcasecmp(subject, "class") == 0)
		subject = "loginclass";
	else if (strcasecmp(subject, "j") == 0)
		subject = "jail";

	if (resolve_ids &&
	    strcasecmp(subject, "user") == 0 && strlen(textid) > 0) {
		error = parse_user(textid, &id, rule);
		if (error != 0) {
			free(tofree);
			return (NULL);
		}
		ret = asprintf(&resolved, "%s:%d:%s", subject, (int)id, rest);
	} else if (resolve_ids &&
	    strcasecmp(subject, "group") == 0 && strlen(textid) > 0) {
		error = parse_group(textid, &id, rule);
		if (error != 0) {
			free(tofree);
			return (NULL);
		}
		ret = asprintf(&resolved, "%s:%d:%s", subject, (int)id, rest);
	} else {
		ret = asprintf(&resolved, "%s:%s:%s", subject, textid, rest);
	}

	if (ret <= 0) {
		warn("asprintf");
		free(tofree);
		return (NULL);
	}

	free(tofree);

	expanded = expand_amount(resolved, rule);
	free(resolved);

	return (expanded);
}