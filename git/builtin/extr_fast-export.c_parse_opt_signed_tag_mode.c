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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGNED_TAG_ABORT ; 
 int /*<<< orphan*/  STRIP ; 
 int /*<<< orphan*/  VERBATIM ; 
 int /*<<< orphan*/  WARN ; 
 int /*<<< orphan*/  WARN_STRIP ; 
 int error (char*,char const*) ; 
 int /*<<< orphan*/  signed_tag_mode ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int parse_opt_signed_tag_mode(const struct option *opt,
				     const char *arg, int unset)
{
	if (unset || !strcmp(arg, "abort"))
		signed_tag_mode = SIGNED_TAG_ABORT;
	else if (!strcmp(arg, "verbatim") || !strcmp(arg, "ignore"))
		signed_tag_mode = VERBATIM;
	else if (!strcmp(arg, "warn"))
		signed_tag_mode = WARN;
	else if (!strcmp(arg, "warn-strip"))
		signed_tag_mode = WARN_STRIP;
	else if (!strcmp(arg, "strip"))
		signed_tag_mode = STRIP;
	else
		return error("Unknown signed-tags mode: %s", arg);
	return 0;
}