#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; struct TYPE_4__* next; } ;
typedef  TYPE_1__ epair_t ;
struct TYPE_5__ {TYPE_1__* epairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_MAP_ENTSTRING ; 
 int /*<<< orphan*/  Q_stricmp (char const*,char*) ; 
 int /*<<< orphan*/  StripTrailing (char*) ; 
 char* ValueForKey (TYPE_2__*,char*) ; 
 char* bspEntData ; 
 int bspEntDataSize ; 
 TYPE_2__* entities ; 
 int numBSPEntities ; 
 int numEntities ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void UnparseEntities( void ){
	int i;
	char        *buf, *end;
	epair_t     *ep;
	char line[ 2048 ];
	char key[ 1024 ], value[ 1024 ];
	const char  *value2;


	/* setup */
	buf = bspEntData;
	end = buf;
	*end = 0;

	/* run through entity list */
	for ( i = 0; i < numBSPEntities && i < numEntities; i++ )
	{
		/* get epair */
		ep = entities[ i ].epairs;
		if ( ep == NULL ) {
			continue;   /* ent got removed */

		}
		/* ydnar: certain entities get stripped from bsp file */
		value2 = ValueForKey( &entities[ i ], "classname" );
		if ( !Q_stricmp( value2, "misc_model" ) ||
			 !Q_stricmp( value2, "_decal" ) ||
			 !Q_stricmp( value2, "_skybox" ) ) {
			continue;
		}

		/* add beginning brace */
		strcat( end, "{\n" );
		end += 2;

		/* walk epair list */
		for ( ep = entities[ i ].epairs; ep != NULL; ep = ep->next )
		{
			/* copy and clean */
			strcpy( key, ep->key );
			StripTrailing( key );
			strcpy( value, ep->value );
			StripTrailing( value );

			/* add to buffer */
			sprintf( line, "\"%s\" \"%s\"\n", key, value );
			strcat( end, line );
			end += strlen( line );
		}

		/* add trailing brace */
		strcat( end,"}\n" );
		end += 2;

		/* check for overflow */
		if ( end > buf + MAX_MAP_ENTSTRING ) {
			Error( "Entity text too long" );
		}
	}

	/* set size */
	bspEntDataSize = end - buf + 1;
}