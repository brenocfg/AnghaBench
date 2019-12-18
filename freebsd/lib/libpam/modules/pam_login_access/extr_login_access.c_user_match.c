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
struct group {scalar_t__* gr_mem; } ;

/* Variables and functions */
 int NO ; 
 int YES ; 
 struct group* getgrnam (char const*) ; 
 int netgroup_match (char const*,char*,char const*) ; 
 scalar_t__ strcasecmp (char const*,scalar_t__) ; 
 scalar_t__ string_match (char const*,char const*) ; 

__attribute__((used)) static int
user_match(const char *tok, const char *string)
{
    struct group *group;
    int     i;

    /*
     * If a token has the magic value "ALL" the match always succeeds.
     * Otherwise, return YES if the token fully matches the username, or if
     * the token is a group that contains the username.
     */

    if (tok[0] == '@') {			/* netgroup */
	return (netgroup_match(tok + 1, (char *) 0, string));
    } else if (string_match(tok, string)) {	/* ALL or exact match */
	return (YES);
    } else if ((group = getgrnam(tok)) != NULL) {/* try group membership */
	for (i = 0; group->gr_mem[i]; i++)
	    if (strcasecmp(string, group->gr_mem[i]) == 0)
		return (YES);
    }
    return (NO);
}