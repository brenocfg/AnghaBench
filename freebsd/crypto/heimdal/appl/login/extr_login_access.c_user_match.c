#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct login_info {TYPE_1__* user; int /*<<< orphan*/  from; } ;
struct group {scalar_t__ gr_gid; scalar_t__* gr_mem; } ;
struct TYPE_2__ {char* pw_name; scalar_t__ pw_gid; } ;

/* Variables and functions */
 int NO ; 
 int YES ; 
 scalar_t__ from_match (char*,struct login_info*) ; 
 struct group* getgrnam (char*) ; 
 int /*<<< orphan*/  myhostname () ; 
 int netgroup_match (char*,char*,char*) ; 
 scalar_t__ strcasecmp (char*,scalar_t__) ; 
 char* strchr (char*,char) ; 
 scalar_t__ string_match (char*,char*) ; 

__attribute__((used)) static int user_match(char *tok, struct login_info *item)
{
    char   *string = item->user->pw_name;
    struct login_info fake_item;
    struct group *group;
    int     i;
    char   *at;

    /*
     * If a token has the magic value "ALL" the match always succeeds.
     * Otherwise, return YES if the token fully matches the username, if the
     * token is a group that contains the username, or if the token is the
     * name of the user's primary group.
     */

    if ((at = strchr(tok + 1, '@')) != 0) {	/* split user@host pattern */
	*at = 0;
	fake_item.from = myhostname();
	return (user_match(tok, item) && from_match(at + 1, &fake_item));
    } else if (tok[0] == '@') {			/* netgroup */
	return (netgroup_match(tok + 1, (char *) 0, string));
    } else if (string_match(tok, string)) {	/* ALL or exact match */
	return (YES);
    } else if ((group = getgrnam(tok)) != 0) { /* try group membership */
	if (item->user->pw_gid == group->gr_gid)
	    return (YES);
	for (i = 0; group->gr_mem[i]; i++)
	    if (strcasecmp(string, group->gr_mem[i]) == 0)
		return (YES);
    }
    return (NO);
}