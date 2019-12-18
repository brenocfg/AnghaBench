#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int filelen; scalar_t__ fileofs; } ;
typedef  TYPE_1__ lump_t ;
struct TYPE_10__ {void* contentFlags; void* surfaceFlags; } ;
typedef  TYPE_2__ dshader_t ;
struct TYPE_12__ {TYPE_2__* (* Hunk_Alloc ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int numShaders; TYPE_2__* shaders; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 void* LittleLong (void*) ; 
 scalar_t__ fileBase ; 
 int /*<<< orphan*/  h_low ; 
 TYPE_5__ ri ; 
 TYPE_4__ s_worldData ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* stub2 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	void R_LoadShaders( lump_t *l ) {	
	int		i, count;
	dshader_t	*in, *out;
	
	in = (void *)(fileBase + l->fileofs);
	if (l->filelen % sizeof(*in))
		ri.Error (ERR_DROP, "LoadMap: funny lump size in %s",s_worldData.name);
	count = l->filelen / sizeof(*in);
	out = ri.Hunk_Alloc ( count*sizeof(*out), h_low );

	s_worldData.shaders = out;
	s_worldData.numShaders = count;

	Com_Memcpy( out, in, count*sizeof(*out) );

	for ( i=0 ; i<count ; i++ ) {
		out[i].surfaceFlags = LittleLong( out[i].surfaceFlags );
		out[i].contentFlags = LittleLong( out[i].contentFlags );
	}
}