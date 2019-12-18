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
typedef  int /*<<< orphan*/  int16 ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  anyErrors ; 
 int errorCount ; 
 int /*<<< orphan*/  exitWithStatus () ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ stop ; 
 int /*<<< orphan*/  writeFunctionName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeTestsPerformed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writeErrorFound( int16 count )
{

    fputc( '\r', stderr );
    if ( errorCount == 1 ) {
        fputs( "Errors found in ", stdout );
        writeFunctionName( stdout );
        fputs( ":\n", stdout );
    }
    if ( stop ) {
        writeTestsPerformed( count );
        exitWithStatus();
    }
    anyErrors = TRUE;

}