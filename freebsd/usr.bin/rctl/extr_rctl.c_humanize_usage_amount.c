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
 int asprintf (char**,char*,char const*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int humanize_number (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ str2int64 (char const*,int /*<<< orphan*/ *) ; 
 char* strdup (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static char *
humanize_usage_amount(char *usage)
{
	int64_t num;
	const char *resource, *amount;
	char *copy, *humanized, buf[6], *tofree;
	int ret;

	tofree = copy = strdup(usage);
	if (copy == NULL)
		err(1, "strdup");

	resource = strsep(&copy, "=");
	amount = copy;

	assert(resource != NULL);
	assert(amount != NULL);

	if (str2int64(amount, &num) != 0 || 
	    humanize_number(buf, sizeof(buf), num, "", HN_AUTOSCALE,
	    HN_DECIMAL | HN_NOSPACE) == -1) {
		free(tofree);
		return (usage);
	}

	ret = asprintf(&humanized, "%s=%s", resource, buf);
	if (ret <= 0)
		err(1, "asprintf");

	free(tofree);
	return (humanized);
}