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
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 scalar_t__ FS_CheckDirTraversal (char const*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strstr (char const*,char*) ; 

qboolean FS_InvalidGameDir( const char *gamedir ) {
	if ( !strcmp( gamedir, "." ) || !strcmp( gamedir, ".." )
		|| !strcmp( gamedir, "/" ) || !strcmp( gamedir, "\\" )
		|| strstr( gamedir, "/.." ) || strstr( gamedir, "\\.." )
		|| FS_CheckDirTraversal( gamedir ) ) {
		return qtrue;
	}

	return qfalse;
}