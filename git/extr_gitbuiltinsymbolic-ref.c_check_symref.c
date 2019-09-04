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

/* Variables and functions */
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  puts (char const*) ; 
 char* resolve_ref_unsafe (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 char* shorten_unambiguous_ref (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_symref(const char *HEAD, int quiet, int shorten, int print)
{
	int flag;
	const char *refname = resolve_ref_unsafe(HEAD, 0, NULL, &flag);

	if (!refname)
		die("No such ref: %s", HEAD);
	else if (!(flag & REF_ISSYMREF)) {
		if (!quiet)
			die("ref %s is not a symbolic ref", HEAD);
		else
			return 1;
	}
	if (print) {
		if (shorten)
			refname = shorten_unambiguous_ref(refname, 0);
		puts(refname);
	}
	return 0;
}