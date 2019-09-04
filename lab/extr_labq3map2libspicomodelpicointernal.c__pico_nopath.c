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
 int /*<<< orphan*/  strchr (char const*,char) ; 
 int strlen (char const*) ; 

const char *_pico_nopath( const char *path ){
	const char *src;

	if ( path == NULL ) {
		return "";
	}
	if ( !strchr( path,'/' ) && !strchr( path,'\\' ) ) {
		return ( path );
	}

	src = path + ( strlen( path ) - 1 );
	while ( ( src-- ) != path )
	{
		if ( *src == '/' || *src == '\\' ) {
			return ( ++src );
		}
	}
	return "";
}