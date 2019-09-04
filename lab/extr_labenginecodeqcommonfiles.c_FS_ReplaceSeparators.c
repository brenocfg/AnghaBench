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
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 char PATH_SEP ; 
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void FS_ReplaceSeparators( char *path ) {
	char	*s;
	qboolean lastCharWasSep = qfalse;

	for ( s = path ; *s ; s++ ) {
		if ( *s == '/' || *s == '\\' ) {
			if ( !lastCharWasSep ) {
				*s = PATH_SEP;
				lastCharWasSep = qtrue;
			} else {
				memmove (s, s + 1, strlen (s));
			}
		} else {
			lastCharWasSep = qfalse;
		}
	}
}