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
struct TYPE_4__ {int filelen; int fileofs; } ;
typedef  TYPE_1__ lump_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_5__ {int clusterBytes; int numClusters; void* visibility; int /*<<< orphan*/  vised; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Com_Memset (void*,int,int) ; 
 void* Hunk_Alloc (int,int /*<<< orphan*/ ) ; 
 void* LittleLong (int) ; 
 int VIS_HEADER ; 
 TYPE_2__ cm ; 
 int /*<<< orphan*/ * cmod_base ; 
 int /*<<< orphan*/  h_high ; 
 int /*<<< orphan*/  qtrue ; 

void CMod_LoadVisibility( lump_t *l ) {
	int		len;
	byte	*buf;

    len = l->filelen;
	if ( !len ) {
		cm.clusterBytes = ( cm.numClusters + 31 ) & ~31;
		cm.visibility = Hunk_Alloc( cm.clusterBytes, h_high );
		Com_Memset( cm.visibility, 255, cm.clusterBytes );
		return;
	}
	buf = cmod_base + l->fileofs;

	cm.vised = qtrue;
	cm.visibility = Hunk_Alloc( len, h_high );
	cm.numClusters = LittleLong( ((int *)buf)[0] );
	cm.clusterBytes = LittleLong( ((int *)buf)[1] );
	Com_Memcpy (cm.visibility, buf + VIS_HEADER, len - VIS_HEADER );
}