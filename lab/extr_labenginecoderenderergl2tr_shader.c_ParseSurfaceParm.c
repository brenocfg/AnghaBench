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
struct TYPE_5__ {int /*<<< orphan*/  contents; int /*<<< orphan*/  surfaceFlags; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  contentFlags; int /*<<< orphan*/  surfaceFlags; } ;

/* Variables and functions */
 int ARRAY_LEN (TYPE_2__*) ; 
 char* COM_ParseExt (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_stricmp (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* infoParms ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_1__ shader ; 

__attribute__((used)) static void ParseSurfaceParm( char **text ) {
	char	*token;
	int		numInfoParms = ARRAY_LEN( infoParms );
	int		i;

	token = COM_ParseExt( text, qfalse );
	for ( i = 0 ; i < numInfoParms ; i++ ) {
		if ( !Q_stricmp( token, infoParms[i].name ) ) {
			shader.surfaceFlags |= infoParms[i].surfaceFlags;
			shader.contentFlags |= infoParms[i].contents;
#if 0
			if ( infoParms[i].clearSolid ) {
				si->contents &= ~CONTENTS_SOLID;
			}
#endif
			break;
		}
	}
}