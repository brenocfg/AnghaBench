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
struct TYPE_4__ {TYPE_1__* scriptstack; int /*<<< orphan*/  filename; } ;
struct TYPE_3__ {int line; } ;

/* Variables and functions */
 int MAX_SOURCEFILES ; 
 int qfalse ; 
 int qtrue ; 
 TYPE_2__** sourceFiles ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

int PC_SourceFileAndLine(int handle, char *filename, int *line)
{
	if (handle < 1 || handle >= MAX_SOURCEFILES)
		return qfalse;
	if (!sourceFiles[handle])
		return qfalse;

	strcpy(filename, sourceFiles[handle]->filename);
	if (sourceFiles[handle]->scriptstack)
		*line = sourceFiles[handle]->scriptstack->line;
	else
		*line = 0;
	return qtrue;
}