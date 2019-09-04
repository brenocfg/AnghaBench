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
typedef  enum date_mode_type { ____Placeholder_date_mode_type } date_mode_type ;

/* Variables and functions */
 int DATE_HUMAN ; 
 int DATE_ISO8601 ; 
 int DATE_ISO8601_STRICT ; 
 int DATE_NORMAL ; 
 int DATE_RAW ; 
 int DATE_RELATIVE ; 
 int DATE_RFC2822 ; 
 int DATE_SHORT ; 
 int DATE_STRFTIME ; 
 int DATE_UNIX ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 

__attribute__((used)) static enum date_mode_type parse_date_type(const char *format, const char **end)
{
	if (skip_prefix(format, "relative", end))
		return DATE_RELATIVE;
	if (skip_prefix(format, "iso8601-strict", end) ||
	    skip_prefix(format, "iso-strict", end))
		return DATE_ISO8601_STRICT;
	if (skip_prefix(format, "iso8601", end) ||
	    skip_prefix(format, "iso", end))
		return DATE_ISO8601;
	if (skip_prefix(format, "rfc2822", end) ||
	    skip_prefix(format, "rfc", end))
		return DATE_RFC2822;
	if (skip_prefix(format, "short", end))
		return DATE_SHORT;
	if (skip_prefix(format, "default", end))
		return DATE_NORMAL;
	if (skip_prefix(format, "human", end))
		return DATE_HUMAN;
	if (skip_prefix(format, "raw", end))
		return DATE_RAW;
	if (skip_prefix(format, "unix", end))
		return DATE_UNIX;
	if (skip_prefix(format, "format", end))
		return DATE_STRFTIME;
	/*
	 * Please update $__git_log_date_formats in
	 * git-completion.bash when you add new formats.
	 */

	die("unknown date format %s", format);
}