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
struct TYPE_4__ {int contentFlagsClear; int contentFlags; int surfaceFlagsClear; int surfaceFlags; int compileFlagsClear; int compileFlags; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ surfaceParm_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {TYPE_1__* surfaceParms; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_stricmp (char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* custSurfaceParms ; 
 TYPE_2__* game ; 
 int numCustSurfaceParms ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean ApplySurfaceParm( char *name, int *contentFlags, int *surfaceFlags, int *compileFlags ){
	int i, fake;
	surfaceParm_t   *sp;


	/* dummy check */
	if ( name == NULL ) {
		name = "";
	}
	if ( contentFlags == NULL ) {
		contentFlags = &fake;
	}
	if ( surfaceFlags == NULL ) {
		surfaceFlags = &fake;
	}
	if ( compileFlags == NULL ) {
		compileFlags = &fake;
	}

	/* walk the current game's surfaceparms */
	sp = game->surfaceParms;
	while ( sp->name != NULL )
	{
		/* match? */
		if ( !Q_stricmp( name, sp->name ) ) {
			/* clear and set flags */
			*contentFlags &= ~( sp->contentFlagsClear );
			*contentFlags |= sp->contentFlags;
			*surfaceFlags &= ~( sp->surfaceFlagsClear );
			*surfaceFlags |= sp->surfaceFlags;
			*compileFlags &= ~( sp->compileFlagsClear );
			*compileFlags |= sp->compileFlags;

			/* return ok */
			return qtrue;
		}

		/* next */
		sp++;
	}

	/* check custom info parms */
	for ( i = 0; i < numCustSurfaceParms; i++ )
	{
		/* get surfaceparm */
		sp = &custSurfaceParms[ i ];

		/* match? */
		if ( !Q_stricmp( name, sp->name ) ) {
			/* clear and set flags */
			*contentFlags &= ~( sp->contentFlagsClear );
			*contentFlags |= sp->contentFlags;
			*surfaceFlags &= ~( sp->surfaceFlagsClear );
			*surfaceFlags |= sp->surfaceFlags;
			*compileFlags &= ~( sp->compileFlagsClear );
			*compileFlags |= sp->compileFlags;

			/* return ok */
			return qtrue;
		}
	}

	/* no matching surfaceparm found */
	return qfalse;
}