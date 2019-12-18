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
 int EOF ; 
 int /*<<< orphan*/  error_message (char*,int) ; 
 int input () ; 
 int lineno ; 

__attribute__((used)) static void
handle_comment(void)
{
    int c;
    int start_lineno = lineno;
    int level = 1;
    int seen_star = 0;
    int seen_slash = 0;
    while((c = input()) != EOF) {
	if(c == '/') {
	    if(seen_star) {
		if(--level == 0)
		    return;
		seen_star = 0;
		continue;
	    }
	    seen_slash = 1;
	    continue;
	} else if(c == '*') {
	    if(seen_slash) {
		level++;
		seen_star = seen_slash = 0;
		continue;
	    }
	    seen_star = 1;
	    continue;
	}
	seen_star = seen_slash = 0;
	if(c == '\n') {
	    lineno++;
	    continue;
	}
    }
    if(c == EOF)
	error_message("unterminated comment, possibly started on line %d\n", start_lineno);
}