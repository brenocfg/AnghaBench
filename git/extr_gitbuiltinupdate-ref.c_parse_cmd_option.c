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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_NO_DEREF ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 char const line_termination ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  update_flags ; 

__attribute__((used)) static const char *parse_cmd_option(struct strbuf *input, const char *next)
{
	const char *rest;
	if (skip_prefix(next, "no-deref", &rest) && *rest == line_termination)
		update_flags |= REF_NO_DEREF;
	else
		die("option unknown: %s", next);
	return rest;
}