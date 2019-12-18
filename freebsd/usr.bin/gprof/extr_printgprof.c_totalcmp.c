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
struct TYPE_2__ {double propself; double propchild; char* name; scalar_t__ cycleno; scalar_t__ ncall; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 int strcmp (char*,char*) ; 

int
totalcmp(const void *v1, const void *v2)
{
    const nltype **npp1 = (const nltype **)v1;
    const nltype **npp2 = (const nltype **)v2;
    register const nltype *np1 = *npp1;
    register const nltype *np2 = *npp2;
    double		diff;

    diff =    ( np1 -> propself + np1 -> propchild )
	    - ( np2 -> propself + np2 -> propchild );
    if ( diff < 0.0 )
	    return 1;
    if ( diff > 0.0 )
	    return -1;
    if ( np1 -> name == 0 && np1 -> cycleno != 0 )
	return -1;
    if ( np2 -> name == 0 && np2 -> cycleno != 0 )
	return 1;
    if ( np1 -> name == 0 )
	return -1;
    if ( np2 -> name == 0 )
	return 1;
    if ( *(np1 -> name) != '_' && *(np2 -> name) == '_' )
	return -1;
    if ( *(np1 -> name) == '_' && *(np2 -> name) != '_' )
	return 1;
    if ( np1 -> ncall > np2 -> ncall )
	return -1;
    if ( np1 -> ncall < np2 -> ncall )
	return 1;
    return strcmp( np1 -> name , np2 -> name );
}