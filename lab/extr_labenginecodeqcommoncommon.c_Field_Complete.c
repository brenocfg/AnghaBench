#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; void* cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q_strcat (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* completionField ; 
 int /*<<< orphan*/ * completionString ; 
 int matchCount ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  shortestMatch ; 
 void* strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static qboolean Field_Complete( void )
{
	int completionOffset;

	if( matchCount == 0 )
		return qtrue;

	completionOffset = strlen( completionField->buffer ) - strlen( completionString );

	Q_strncpyz( &completionField->buffer[ completionOffset ], shortestMatch,
		sizeof( completionField->buffer ) - completionOffset );

	completionField->cursor = strlen( completionField->buffer );

	if( matchCount == 1 )
	{
		Q_strcat( completionField->buffer, sizeof( completionField->buffer ), " " );
		completionField->cursor++;
		return qtrue;
	}

	Com_Printf( "]%s\n", completionField->buffer );

	return qfalse;
}