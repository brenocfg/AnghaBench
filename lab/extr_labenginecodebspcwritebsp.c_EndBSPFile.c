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

/* Variables and functions */
 int /*<<< orphan*/  EmitBrushes () ; 
 int /*<<< orphan*/  EmitPlanes () ; 
 int /*<<< orphan*/  Q2_UnparseEntities () ; 

void EndBSPFile (void)
{
#if 0
	char	path[1024];
	int		len;
	byte	*buf;
#endif


	EmitBrushes ();
	EmitPlanes ();
	Q2_UnparseEntities ();

	// load the pop
#if 0
	sprintf (path, "%s/pics/pop.lmp", gamedir);
	len = LoadFile (path, &buf);
	memcpy (dpop, buf, sizeof(dpop));
	FreeMemory(buf);
#endif
}