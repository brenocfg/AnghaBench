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
 int strlen (char const*) ; 

char *_pico_setfext( char *path, const char *ext ){
	char *src;
	int remfext = 0;

	src = path + ( strlen( path ) - 1 );

	if ( ext == NULL ) {
		ext = "";
	}
	if ( strlen( ext ) < 1 ) {
		remfext = 1;
	}
	if ( strlen( path ) < 1 ) {
		return path;
	}

	while ( ( src-- ) != path )
	{
		if ( *src == '/' || *src == '\\' ) {
			return path;
		}

		if ( *src == '.' ) {
			if ( remfext ) {
				*src = '\0';
				return path;
			}
			*( ++src ) = '\0';
			break;
		}
	}
	strcat( path,ext );
	return path;
}