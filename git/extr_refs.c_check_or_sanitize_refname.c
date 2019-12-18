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
struct strbuf {scalar_t__ len; } ;

/* Variables and functions */
 int REFNAME_ALLOW_ONELEVEL ; 
 int check_refname_component (char const*,int*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_complete (struct strbuf*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int check_or_sanitize_refname(const char *refname, int flags,
				     struct strbuf *sanitized)
{
	int component_len, component_count = 0;

	if (!strcmp(refname, "@")) {
		/* Refname is a single character '@'. */
		if (sanitized)
			strbuf_addch(sanitized, '-');
		else
			return -1;
	}

	while (1) {
		if (sanitized && sanitized->len)
			strbuf_complete(sanitized, '/');

		/* We are at the start of a path component. */
		component_len = check_refname_component(refname, &flags,
							sanitized);
		if (sanitized && component_len == 0)
			; /* OK, omit empty component */
		else if (component_len <= 0)
			return -1;

		component_count++;
		if (refname[component_len] == '\0')
			break;
		/* Skip to next component. */
		refname += component_len + 1;
	}

	if (refname[component_len - 1] == '.') {
		/* Refname ends with '.'. */
		if (sanitized)
			; /* omit ending dot */
		else
			return -1;
	}
	if (!(flags & REFNAME_ALLOW_ONELEVEL) && component_count < 2)
		return -1; /* Refname has only one component. */
	return 0;
}