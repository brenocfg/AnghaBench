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
struct TYPE_2__ {int n_strx; } ;
struct nlist {int n_type; TYPE_1__ n_un; } ;

/* Variables and functions */
 int FALSE ; 
 int N_EXT ; 
 int N_TEXT ; 
 int TRUE ; 
 scalar_t__ aflag ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strtab ; 
 scalar_t__ uflag ; 

__attribute__((used)) static bool
funcsymbol(struct nlist *nlistp)
{
    char	*name, c;

	/*
	 *	must be a text symbol,
	 *	and static text symbols don't qualify if aflag set.
	 */
    if ( ! (  ( nlistp -> n_type == ( N_TEXT | N_EXT ) )
	   || ( ( nlistp -> n_type == N_TEXT ) && ( aflag == 0 ) ) ) ) {
	return FALSE;
    }
	/*
	 *	name must start with an underscore if uflag is set.
	 *	can't have any `funny' characters in name,
	 *	where `funny' means `.' (.o file names)
	 *	need to make an exception for sparc .mul & co.
	 *	perhaps we should just drop this code entirely...
	 */
    name = strtab + nlistp -> n_un.n_strx;
    if ( uflag && *name != '_' )
	return FALSE;
#ifdef sparc
    if ( *name == '.' ) {
	char *p = name + 1;
	if ( *p == 'u' )
	    p++;
	if ( strcmp ( p, "mul" ) == 0 || strcmp ( p, "div" ) == 0 ||
	     strcmp ( p, "rem" ) == 0 )
		return TRUE;
    }
#endif
    while ( (c = *name++) ) {
	if ( c == '.' ) {
	    return FALSE;
	}
    }
    return TRUE;
}