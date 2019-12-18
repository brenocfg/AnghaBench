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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

void
printblurb(const char *blurbname)
{
    FILE	*blurbfile;
    int		input;

    blurbfile = fopen( blurbname , "r" );
    if ( blurbfile == NULL ) {
	warn( "%s" , blurbname );
	return;
    }
    while ( ( input = getc( blurbfile ) ) != EOF ) {
	putchar( input );
    }
    fclose( blurbfile );
}