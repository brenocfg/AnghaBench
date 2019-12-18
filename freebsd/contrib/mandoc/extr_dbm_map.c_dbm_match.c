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
struct dbm_match {int type; int /*<<< orphan*/  re; int /*<<< orphan*/  str; } ;

/* Variables and functions */
#define  DBM_EXACT 130 
#define  DBM_REGEX 129 
#define  DBM_SUB 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  regexec (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strcasestr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

int
dbm_match(const struct dbm_match *match, const char *str)
{
	switch (match->type) {
	case DBM_EXACT:
		return strcmp(str, match->str) == 0;
	case DBM_SUB:
		return strcasestr(str, match->str) != NULL;
	case DBM_REGEX:
		return regexec(match->re, str, 0, NULL, 0) == 0;
	default:
		abort();
	}
}