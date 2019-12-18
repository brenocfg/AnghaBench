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
 int MAXPNSTR ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void
pnstr( char* s, int c )
{
    char string[ MAXPNSTR + 1 ];

    if ( c > MAXPNSTR )
        c = MAXPNSTR;
    strncpy( string, s, c );
    string[ c ] = '\0';
    printf( "%s", string );
}