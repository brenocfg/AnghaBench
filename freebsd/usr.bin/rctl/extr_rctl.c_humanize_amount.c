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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int HN_DECIMAL ; 
 int HN_NOSPACE ; 
 int asprintf (char**,char*,char const*,char const*,char const*,char const*,char*,...) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int humanize_number (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ str2int64 (char const*,int /*<<< orphan*/ *) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static char *
humanize_amount(char *rule)
{
	int64_t num;
	const char *subject, *subject_id, *resource, *action, *amount, *per;
	char *copy, *humanized, buf[6], *tofree;
	int ret;

	tofree = copy = strdup(rule);
	if (copy == NULL)
		err(1, "strdup");

	subject = strsep(&copy, ":");
	subject_id = strsep(&copy, ":");
	resource = strsep(&copy, ":");
	action = strsep(&copy, "=/");
	amount = strsep(&copy, "/");
	per = copy;

	if (amount == NULL || strlen(amount) == 0 ||
	    str2int64(amount, &num) != 0) {
		free(tofree);
		return (rule);
	}

	assert(subject != NULL);
	assert(subject_id != NULL);
	assert(resource != NULL);
	assert(action != NULL);

	if (humanize_number(buf, sizeof(buf), num, "", HN_AUTOSCALE,
	    HN_DECIMAL | HN_NOSPACE) == -1)
		err(1, "humanize_number");

	if (per == NULL) {
		ret = asprintf(&humanized, "%s:%s:%s:%s=%s",
		    subject, subject_id, resource, action, buf);
	} else {
		ret = asprintf(&humanized, "%s:%s:%s:%s=%s/%s",
		    subject, subject_id, resource, action, buf, per);
	}

	if (ret <= 0)
		err(1, "asprintf");

	free(tofree);
	return (humanized);
}