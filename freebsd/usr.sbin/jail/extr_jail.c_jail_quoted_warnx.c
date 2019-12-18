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
struct cfjail {char* name; int /*<<< orphan*/ * intparams; } ;

/* Variables and functions */
 size_t KP_JID ; 
 size_t KP_NAME ; 
 char* string_param (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char const*,...) ; 

__attribute__((used)) static void
jail_quoted_warnx(const struct cfjail *j, const char *name_msg,
    const char *noname_msg)
{
	const char *pval;

	if ((pval = j->name) || (pval = string_param(j->intparams[KP_JID])) ||
	    (pval = string_param(j->intparams[KP_NAME])))
		warnx("\"%s\" %s", pval, name_msg);
	else
		warnx("%s", noname_msg);
}