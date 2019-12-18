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
typedef  char Char ;

/* Variables and functions */
 int ADDOP ; 
 int EQEQ ; 
 int EQMATCH ; 
 int EQOP ; 
 int GTR ; 
 int LSS ; 
 int MULOP ; 
 int NOTEQ ; 
 int NOTEQMATCH ; 
 int RELOP ; 
 int RESTOP ; 

__attribute__((used)) static int
isa(Char *cp, int what)
{
    if (cp == 0)
	return ((what & RESTOP) != 0);
    if (*cp == '\0')
    	return 0;
    if (cp[1] == 0) {
	if (what & ADDOP && (*cp == '+' || *cp == '-'))
	    return (1);
	if (what & MULOP && (*cp == '*' || *cp == '/' || *cp == '%'))
	    return (1);
	if (what & RESTOP && (*cp == '(' || *cp == ')' || *cp == '!' ||
			      *cp == '~' || *cp == '^' || *cp == '"'))
	    return (1);
    }
    else if (cp[2] == 0) {
	if (what & RESTOP) {
	    if (cp[0] == '|' && cp[1] == '&')
		return (1);
	    if (cp[0] == '<' && cp[1] == '<')
		return (1);
	    if (cp[0] == '>' && cp[1] == '>')
		return (1);
	}
	if (what & EQOP) {
	    if (cp[0] == '=') {
		if (cp[1] == '=')
		    return (EQEQ);
		if (cp[1] == '~')
		    return (EQMATCH);
	    }
	    else if (cp[0] == '!') {
		if (cp[1] == '=')
		    return (NOTEQ);
		if (cp[1] == '~')
		    return (NOTEQMATCH);
	    }
	}
    }
    if (what & RELOP) {
	if (*cp == '<')
	    return (LSS);
	if (*cp == '>')
	    return (GTR);
    }
    return (0);
}