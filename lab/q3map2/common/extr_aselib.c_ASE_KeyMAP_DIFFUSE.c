#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t numMaterials; TYPE_1__* materials; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASE_GetToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,char*) ; 
 TYPE_2__ ase ; 
 char* gamedir ; 
 char* gl_filename ; 
 int /*<<< orphan*/  qfalse ; 
 char* s_token ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void ASE_KeyMAP_DIFFUSE( const char *token ){
	char bitmap[1024];
	char filename[1024];
	int i = 0;

	strcpy( filename, gl_filename );

	if ( !strcmp( token, "*BITMAP" ) ) {
		ASE_GetToken( qfalse );

		// the purpose of this whole chunk of code below is to extract the relative path
		// from a full path in the ASE

		strcpy( bitmap, s_token + 1 );
		if ( strchr( bitmap, '"' ) ) {
			*strchr( bitmap, '"' ) = 0;
		}

		/* convert backslash to slash */
		while ( bitmap[i] )
		{
			if ( bitmap[i] == '\\' ) {
				bitmap[i] = '/';
			}
			i++;
		}

		/* remove filename from path */
		for ( i = strlen( filename ); i > 0; i-- )
		{
			if ( filename[i] == '/' ) {
				filename[i] = '\0';
				break;
			}
		}

		/* replaces a relative path with a full path */
		if ( bitmap[0] == '.' && bitmap[1] == '.' && bitmap[2] == '/' ) {
			while ( bitmap[0] == '.' && bitmap[1] == '.' && bitmap[2] == '/' )
			{
				/* remove last item from path */
				for ( i = strlen( filename ); i > 0; i-- )
				{
					if ( filename[i] == '/' ) {
						filename[i] = '\0';
						break;
					}
				}
				strcpy( bitmap, &bitmap[3] );
			}
			strcat( filename, "/" );
			strcat( filename, bitmap );
			strcpy( bitmap, filename );
		}

		if ( strstr( bitmap, gamedir ) ) {
			strcpy( ase.materials[ase.numMaterials].name, strstr( bitmap, gamedir ) + strlen( gamedir ) );
			Sys_Printf( "material name: \'%s\'\n", strstr( bitmap, gamedir ) + strlen( gamedir ) );
		}
		else
		{
			sprintf( ase.materials[ase.numMaterials].name, "(not converted: '%s')", bitmap );
			Sys_FPrintf( SYS_WRN, "WARNING: illegal material name '%s'\n", bitmap );
		}
	}
	else
	{
	}
}