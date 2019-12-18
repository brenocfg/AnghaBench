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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int asprintf (char**,char*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ expand_number (char const*,scalar_t__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char const*) ; 

__attribute__((used)) static char *
expand_amount(const char *rule, const char *unexpanded_rule)
{
	uint64_t num;
	const char *subject, *subject_id, *resource, *action, *amount, *per;
	char *copy, *expanded, *tofree;
	int ret;

	tofree = copy = strdup(rule);
	if (copy == NULL) {
		warn("strdup");
		return (NULL);
	}

	subject = strsep(&copy, ":");
	subject_id = strsep(&copy, ":");
	resource = strsep(&copy, ":");
	action = strsep(&copy, "=/");
	amount = strsep(&copy, "/");
	per = copy;

	if (amount == NULL || strlen(amount) == 0) {
		/*
		 * The "copy" has already been tinkered with by strsep().
		 */
		free(tofree);
		copy = strdup(rule);
		if (copy == NULL) {
			warn("strdup");
			return (NULL);
		}
		return (copy);
	}

	assert(subject != NULL);
	assert(subject_id != NULL);
	assert(resource != NULL);
	assert(action != NULL);

	if (expand_number(amount, &num)) {
		warnx("malformed rule '%s': invalid numeric value '%s'",
		    unexpanded_rule, amount);
		free(tofree);
		return (NULL);
	}

	if (per == NULL) {
		ret = asprintf(&expanded, "%s:%s:%s:%s=%ju",
		    subject, subject_id, resource, action, (uintmax_t)num);
	} else {
		ret = asprintf(&expanded, "%s:%s:%s:%s=%ju/%s",
		    subject, subject_id, resource, action, (uintmax_t)num, per);
	}

	if (ret <= 0) {
		warn("asprintf");
		free(tofree);
		return (NULL);
	}

	free(tofree);

	return (expanded);
}