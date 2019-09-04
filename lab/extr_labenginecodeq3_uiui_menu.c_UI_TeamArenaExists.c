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
typedef  int /*<<< orphan*/  dirlist ;

/* Variables and functions */
 int /*<<< orphan*/  BASETA ; 
 scalar_t__ Q_stricmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int strlen (char*) ; 
 int trap_FS_GetFileList (char*,char*,char*,int) ; 

__attribute__((used)) static qboolean UI_TeamArenaExists( void ) {
	int		numdirs;
	char	dirlist[2048];
	char	*dirptr;
  char  *descptr;
	int		i;
	int		dirlen;

	numdirs = trap_FS_GetFileList( "$modlist", "", dirlist, sizeof(dirlist) );
	dirptr  = dirlist;
	for( i = 0; i < numdirs; i++ ) {
		dirlen = strlen( dirptr ) + 1;
    descptr = dirptr + dirlen;
		if (Q_stricmp(dirptr, BASETA) == 0) {
			return qtrue;
		}
    dirptr += dirlen + strlen(descptr) + 1;
	}
	return qfalse;
}