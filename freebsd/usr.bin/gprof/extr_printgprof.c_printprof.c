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
typedef  int /*<<< orphan*/  nltype ;

/* Variables and functions */
 double actime ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  flatprofheader () ; 
 int /*<<< orphan*/  flatprofline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nl ; 
 int nname ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timecmp ; 

void
printprof(void)
{
    register nltype	*np;
    nltype		**sortednlp;
    int			idx;

    actime = 0.0;
    printf( "\f\n" );
    flatprofheader();
	/*
	 *	Sort the symbol table in by time
	 */
    sortednlp = (nltype **) calloc( nname , sizeof(nltype *) );
    if ( sortednlp == (nltype **) 0 )
	errx( 1 , "[printprof] ran out of memory for time sorting" );
    for ( idx = 0 ; idx < nname ; idx += 1 ) {
	sortednlp[ idx ] = &nl[ idx ];
    }
    qsort( sortednlp , nname , sizeof(nltype *) , timecmp );
    for ( idx = 0 ; idx < nname ; idx += 1 ) {
	np = sortednlp[ idx ];
	flatprofline( np );
    }
    actime = 0.0;
    free( sortednlp );
}