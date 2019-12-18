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

/* Variables and functions */
 int NO ; 
 int /*<<< orphan*/  sep ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 
 int stub1 (char const*,char const*) ; 

__attribute__((used)) static int
list_match(char *list, const char *item,
    int (*match_fn)(const char *, const char *))
{
    char   *tok;
    int     match = NO;

    /*
     * Process tokens one at a time. We have exhausted all possible matches
     * when we reach an "EXCEPT" token or the end of the list. If we do find
     * a match, look for an "EXCEPT" list and recurse to determine whether
     * the match is affected by any exceptions.
     */

    for (tok = strtok(list, sep); tok != NULL; tok = strtok((char *) 0, sep)) {
	if (strcasecmp(tok, "EXCEPT") == 0)	/* EXCEPT: give up */
	    break;
	if ((match = (*match_fn)(tok, item)) != 0)	/* YES */
	    break;
    }
    /* Process exceptions to matches. */

    if (match != NO) {
	while ((tok = strtok((char *) 0, sep)) && strcasecmp(tok, "EXCEPT"))
	     /* VOID */ ;
	if (tok == NULL || list_match((char *) 0, item, match_fn) == NO)
	    return (match);
    }
    return (NO);
}