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
struct _s_x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*,char const*,char const*) ; 
 int match_token_relaxed (struct _s_x*,char const*) ; 

int
get_token(struct _s_x *table, const char *string, const char *errbase)
{
	int tcmd;

	if ((tcmd = match_token_relaxed(table, string)) < 0)
		errx(EX_USAGE, "%s %s %s",
		    (tcmd == 0) ? "invalid" : "ambiguous", errbase, string);

	return (tcmd);
}