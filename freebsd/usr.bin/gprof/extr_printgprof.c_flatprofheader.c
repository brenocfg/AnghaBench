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
 double HISTORICAL_SCALE_2 ; 
 int /*<<< orphan*/  _PATH_FLAT_BLURB ; 
 scalar_t__ bflag ; 
 double hz ; 
 int /*<<< orphan*/  printblurb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 double scale ; 
 double totime ; 

void
flatprofheader(void)
{

    if ( bflag ) {
	printblurb( _PATH_FLAT_BLURB );
    }
    printf( "\ngranularity: each sample hit covers %g byte(s)" ,
	    scale * HISTORICAL_SCALE_2 );
    if ( totime > 0.0 ) {
	printf( " for %.2f%% of %.2f seconds\n\n" ,
		100.0/totime , totime / hz );
    } else {
	printf( " no time accumulated\n\n" );
	    /*
	     *	this doesn't hurt since all the numerators will be zero.
	     */
	totime = 1.0;
    }
    printf( "%5.5s %10.10s %8.8s %8.8s %8.8s %8.8s  %-8.8s\n" ,
	    "%  " , "cumulative" , "self  " , "" , "self  " , "total " , "" );
    printf( "%5.5s %10.10s %8.8s %8.8s %8.8s %8.8s  %-8.8s\n" ,
	    "time" , "seconds " , "seconds" , "calls" ,
	    hz >= 10000000 ? "ns/call" : hz >= 10000 ? "us/call" : "ms/call" ,
	    hz >= 10000000 ? "ns/call" : hz >= 10000 ? "us/call" : "ms/call" ,
	    "name" );
}