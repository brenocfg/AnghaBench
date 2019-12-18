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
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  Error (char*,char const*,int /*<<< orphan*/ ) ; 
 int _mkdir (char const*) ; 
 scalar_t__ errno ; 
 int mkdir (char const*,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

void Q_mkdir( const char *path ){
#ifdef WIN32
	if ( _mkdir( path ) != -1 ) {
		return;
	}
#else
	if ( mkdir( path, 0777 ) != -1 ) {
		return;
	}
#endif
	if ( errno != EEXIST ) {
		Error( "mkdir %s: %s",path, strerror( errno ) );
	}
}