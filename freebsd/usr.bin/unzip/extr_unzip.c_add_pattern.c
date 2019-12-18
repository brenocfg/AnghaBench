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
struct pattern_list {int dummy; } ;
struct pattern {int /*<<< orphan*/  pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (struct pattern_list*,struct pattern*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (char*,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  link ; 
 struct pattern* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
add_pattern(struct pattern_list *list, const char *pattern)
{
	struct pattern *entry;
	size_t len;

	debug("adding pattern '%s'\n", pattern);
	len = strlen(pattern);
	if ((entry = malloc(sizeof *entry + len + 1)) == NULL) {
		errno = ENOMEM;
		error("malloc()");
	}
	memcpy(entry->pattern, pattern, len + 1);
	STAILQ_INSERT_TAIL(list, entry, link);
}