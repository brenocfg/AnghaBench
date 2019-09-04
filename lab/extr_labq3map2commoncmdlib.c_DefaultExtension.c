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
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int strlen (char*) ; 

void DefaultExtension( char *path, const char *extension ){
	char    *src;
//
// if path doesnt have a .EXT, append extension
// (extension should include the .)
//
	src = path + strlen( path ) - 1;

	while ( *src != '/' && *src != '\\' && src != path )
	{
		if ( *src == '.' ) {
			return;                 // it has an extension
		}
		src--;
	}

	strcat( path, extension );
}