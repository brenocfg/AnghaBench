#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ VFS_PAKFILE ;
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_2__ GSList ;

/* Variables and functions */
 int NAME_MAX ; 
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 char* g_ascii_strdown (char*,int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int g_numDirs ; 
 TYPE_2__* g_pakFiles ; 
 TYPE_2__* g_slist_next (TYPE_2__*) ; 
 char const** g_strDirs ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  vfsFixDOSName (char*) ; 

int vfsGetFileCount( const char *filename ){
	int i, count = 0;
	char fixed[NAME_MAX], tmp[NAME_MAX];
	char *lower;
	GSList *lst;

	strcpy( fixed, filename );
	vfsFixDOSName( fixed );
	lower = g_ascii_strdown( fixed, -1 );

	for ( lst = g_pakFiles; lst != NULL; lst = g_slist_next( lst ) )
	{
		VFS_PAKFILE* file = (VFS_PAKFILE*)lst->data;

		if ( strcmp( file->name, lower ) == 0 ) {
			count++;
		}
	}

	for ( i = 0; i < g_numDirs; i++ )
	{
		strcpy( tmp, g_strDirs[i] );
		strcat( tmp, lower );
		if ( access( tmp, R_OK ) == 0 ) {
			count++;
		}
	}
	g_free( lower );
	return count;
}