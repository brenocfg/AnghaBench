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
struct passwd {char* pw_dir; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 char* Q_strncpyz (char*,char*,int) ; 
 char* getenv (char*) ; 
 scalar_t__ getpwuid_r (int /*<<< orphan*/ ,struct passwd*,char*,int,struct passwd**) ; 
 int /*<<< orphan*/  getuid () ; 

char *LokiGetHomeDir( void ){
	#ifndef Q_UNIX
	return NULL;
	#else
	static char	buf[ 4096 ];
	struct passwd   pw, *pwp;
	char            *home;


	/* get the home environment variable */
	home = getenv( "HOME" );
	if ( home ) {
		return Q_strncpyz( buf, home, sizeof( buf ) );
	}

	/* look up home dir in password database */
	if ( getpwuid_r( getuid(), &pw, buf, sizeof( buf ), &pwp ) == 0 ) {
		return pw.pw_dir;
	}

	return NULL;
	#endif
}