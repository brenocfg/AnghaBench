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
typedef  int int16 ;

/* Variables and functions */
 int errorCount ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int tenthousandsCount ; 
 int /*<<< orphan*/  writeFunctionName (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writeTestsPerformed( int16 count )
{

    if ( tenthousandsCount ) {
        fprintf(
            stderr, "\r%d%04d tests performed", tenthousandsCount, count );
    }
    else {
        fprintf( stderr, "\r%d tests performed", count );
    }
    if ( errorCount ) {
        fprintf(
            stderr,
            "; %d error%s found.\n",
            errorCount,
            ( errorCount == 1 ) ? "" : "s"
        );
    }
    else {
        fputs( ".\n", stderr );
        fputs( "No errors found in ", stdout );
        writeFunctionName( stdout );
        fputs( ".\n", stdout );
        fflush( stdout );
    }

}