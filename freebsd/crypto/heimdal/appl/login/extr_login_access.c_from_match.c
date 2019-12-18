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
struct login_info {char* from; } ;

/* Variables and functions */
 int NO ; 
 int YES ; 
 int netgroup_match (char*,char*,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ string_match (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int from_match(char *tok, struct login_info *item)
{
    char   *string = item->from;
    int     tok_len;
    int     str_len;

    /*
     * If a token has the magic value "ALL" the match always succeeds. Return
     * YES if the token fully matches the string. If the token is a domain
     * name, return YES if it matches the last fields of the string. If the
     * token has the magic value "LOCAL", return YES if the string does not
     * contain a "." character. If the token is a network number, return YES
     * if it matches the head of the string.
     */

    if (tok[0] == '@') {			/* netgroup */
	return (netgroup_match(tok + 1, string, (char *) 0));
    } else if (string_match(tok, string)) {	/* ALL or exact match */
	return (YES);
    } else if (tok[0] == '.') {			/* domain: match last fields */
	if ((str_len = strlen(string)) > (tok_len = strlen(tok))
	    && strcasecmp(tok, string + str_len - tok_len) == 0)
	    return (YES);
    } else if (strcasecmp(tok, "LOCAL") == 0) {	/* local: no dots */
	if (strchr(string, '.') == 0)
	    return (YES);
    } else if (tok[(tok_len = strlen(tok)) - 1] == '.'	/* network */
	       && strncmp(tok, string, tok_len) == 0) {
	return (YES);
    }
    return (NO);
}