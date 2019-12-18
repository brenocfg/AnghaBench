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
struct stringlist {int /*<<< orphan*/  string; struct stringlist* next; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

bool
onlist(struct stringlist *listp, const char *funcname)
{
    struct stringlist	*slp;

    for ( slp = listp -> next ; slp ; slp = slp -> next ) {
	if ( ! strcmp( slp -> string , funcname ) ) {
	    return TRUE;
	}
	if ( funcname[0] == '_' && ! strcmp( slp -> string , &funcname[1] ) ) {
	    return TRUE;
	}
    }
    return FALSE;
}