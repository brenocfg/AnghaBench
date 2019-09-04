#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* shader; scalar_t__ finished; } ;
typedef  TYPE_1__ shaderInfo_t ;

/* Variables and functions */
 TYPE_1__* AllocShaderInfo () ; 
 int /*<<< orphan*/  FinishShader (TYPE_1__*) ; 
 int /*<<< orphan*/  LoadShaderImages (TYPE_1__*) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  StripExtension (char*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 int numShaderInfo ; 
 scalar_t__ qfalse ; 
 TYPE_1__* shaderInfo ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

shaderInfo_t *ShaderInfoForShader( const char *shaderName ){
	int i;
	shaderInfo_t    *si;
	char shader[ MAX_QPATH ];


	/* dummy check */
	if ( shaderName == NULL || shaderName[ 0 ] == '\0' ) {
		Sys_FPrintf( SYS_WRN, "WARNING: Null or empty shader name\n" );
		shaderName = "missing";
	}

	/* strip off extension */
	strcpy( shader, shaderName );
	StripExtension( shader );

	/* search for it */
	for ( i = 0; i < numShaderInfo; i++ )
	{
		si = &shaderInfo[ i ];
		if ( !Q_stricmp( shader, si->shader ) ) {
			/* load image if necessary */
			if ( si->finished == qfalse ) {
				LoadShaderImages( si );
				FinishShader( si );
			}

			/* return it */
			return si;
		}
	}

	/* allocate a default shader */
	si = AllocShaderInfo();
	strcpy( si->shader, shader );
	LoadShaderImages( si );
	FinishShader( si );

	/* return it */
	return si;
}