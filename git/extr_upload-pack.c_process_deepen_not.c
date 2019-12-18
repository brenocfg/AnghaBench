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
struct string_list {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 int expand_ref (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct object_id*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int process_deepen_not(const char *line, struct string_list *deepen_not, int *deepen_rev_list)
{
	const char *arg;
	if (skip_prefix(line, "deepen-not ", &arg)) {
		char *ref = NULL;
		struct object_id oid;
		if (expand_ref(the_repository, arg, strlen(arg), &oid, &ref) != 1)
			die("git upload-pack: ambiguous deepen-not: %s", line);
		string_list_append(deepen_not, ref);
		free(ref);
		*deepen_rev_list = 1;
		return 1;
	}
	return 0;
}