#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_8__ {struct TYPE_8__* value; struct TYPE_8__* key; struct TYPE_8__* next; } ;
typedef  TYPE_1__ epair_t ;
struct TYPE_9__ {TYPE_1__* epairs; } ;
typedef  TYPE_2__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,int,...) ; 
 int IntForKey (TYPE_2__*,char*) ; 
 int LS_NONE ; 
 int LS_NORMAL ; 
 int MAX_SWITCHED_LIGHTS ; 
 scalar_t__ Q_strncasecmp (char const*,char*,int) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SetKeyValue (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* ValueForKey (TYPE_2__*,char*) ; 
 TYPE_2__* entities ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int numEntities ; 
 int /*<<< orphan*/  numStrippedLights ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

void SetLightStyles( void ){
	int i, j, style, numStyles;
	qboolean keepLights;
	qboolean noRadiosityLight;
	const char  *t;
	entity_t    *e;
	epair_t     *ep, *next;
	char value[ 10 ];
	char lightTargets[ MAX_SWITCHED_LIGHTS ][ 64 ];
	int lightStyles[ MAX_SWITCHED_LIGHTS ];


	/* ydnar: determine if we keep lights in the bsp */
	t = ValueForKey( &entities[ 0 ], "_keepLights" );
	keepLights = ( t[ 0 ] == '1' ) ? qtrue : qfalse;

	/* any light that is controlled (has a targetname) must have a unique style number generated for it */
	numStyles = 0;
	for ( i = 1; i < numEntities; i++ )
	{
		e = &entities[ i ];

		t = ValueForKey( e, "classname" );
		if ( Q_strncasecmp( t, "light", 5 ) ) {
			continue;
		}
		t = ValueForKey( e, "noradiosity" );
		noRadiosityLight = ( t[ 0 ] == '1' ) ? qtrue : qfalse;
		t = ValueForKey( e, "targetname" );
		if ( t[ 0 ] == '\0' ) {
			/* ydnar: strip the light from the BSP file */
			/* neumond: pass all dynamic lights to BSP regardless of keepLights.
				pass all lights (radiosity+dynamic) to BSP if keepLights */
			if ( keepLights == qfalse && noRadiosityLight == qfalse ) {
				ep = e->epairs;
				while ( ep != NULL )
				{
					next = ep->next;
					free( ep->key );
					free( ep->value );
					free( ep );
					ep = next;
				}
				e->epairs = NULL;
				numStrippedLights++;
			}

			/* next light */
			continue;
		}

		/* get existing style */
		style = IntForKey( e, "style" );
		if ( style < LS_NORMAL || style > LS_NONE ) {
			Error( "Invalid lightstyle (%d) on entity %d", style, i );
		}

		/* find this targetname */
		for ( j = 0; j < numStyles; j++ )
			if ( lightStyles[ j ] == style && !strcmp( lightTargets[ j ], t ) ) {
				break;
			}

		/* add a new style */
		if ( j >= numStyles ) {
			if ( numStyles == MAX_SWITCHED_LIGHTS ) {
				Error( "MAX_SWITCHED_LIGHTS (%d) exceeded, reduce the number of lights with targetnames", MAX_SWITCHED_LIGHTS );
			}
			strcpy( lightTargets[ j ], t );
			lightStyles[ j ] = style;
			numStyles++;
		}

		/* set explicit style */
		sprintf( value, "%d", 32 + j );
		SetKeyValue( e, "style", value );

		/* set old style */
		if ( style != LS_NORMAL ) {
			sprintf( value, "%d", style );
			SetKeyValue( e, "switch_style", value );
		}
	}

	/* emit some statistics */
	Sys_FPrintf( SYS_VRB, "%9d light entities stripped\n", numStrippedLights );
}