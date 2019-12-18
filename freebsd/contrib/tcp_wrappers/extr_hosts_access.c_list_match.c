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
struct request_info {int dummy; } ;

/* Variables and functions */
 int NO ; 
 scalar_t__ STR_EQ (char*,char*) ; 
 scalar_t__ STR_NE (char*,char*) ; 
 int /*<<< orphan*/  sep ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int list_match(char *list, struct request_info *request,
    int (*match_fn)(char *, struct request_info *))
{
    char   *tok;

    /*
     * Process tokens one at a time. We have exhausted all possible matches
     * when we reach an "EXCEPT" token or the end of the list. If we do find
     * a match, look for an "EXCEPT" list and recurse to determine whether
     * the match is affected by any exceptions.
     */

    for (tok = strtok(list, sep); tok != 0; tok = strtok((char *) 0, sep)) {
	if (STR_EQ(tok, "EXCEPT"))		/* EXCEPT: give up */
	    return (NO);
	if (match_fn(tok, request)) {		/* YES: look for exceptions */
	    while ((tok = strtok((char *) 0, sep)) && STR_NE(tok, "EXCEPT"))
		 /* VOID */ ;
	    return (tok == 0 || list_match((char *) 0, request, match_fn) == 0);
	}
    }
    return (NO);
}