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
 int /*<<< orphan*/  REENCODE_ABORT ; 
 int /*<<< orphan*/  REENCODE_NO ; 
 int /*<<< orphan*/  REENCODE_YES ; 
 int error (char*,char const*) ; 
 int git_parse_maybe_bool (char const*) ; 
 int /*<<< orphan*/  reencode_mode ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static int parse_opt_reencode_mode(const struct option *opt,
				   const char *arg, int unset)
{
	if (unset) {
		reencode_mode = REENCODE_ABORT;
		return 0;
	}

	switch (git_parse_maybe_bool(arg)) {
	case 0:
		reencode_mode = REENCODE_NO;
		break;
	case 1:
		reencode_mode = REENCODE_YES;
		break;
	default:
		if (!strcasecmp(arg, "abort"))
			reencode_mode = REENCODE_ABORT;
		else
			return error("Unknown reencoding mode: %s", arg);
	}

	return 0;
}