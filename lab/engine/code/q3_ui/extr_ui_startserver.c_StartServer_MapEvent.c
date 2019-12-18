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
struct TYPE_3__ {scalar_t__ id; } ;
typedef  TYPE_1__ menucommon_s ;
struct TYPE_4__ {int page; scalar_t__ currentmap; } ;

/* Variables and functions */
 scalar_t__ ID_PICTURES ; 
 int MAX_MAPSPERPAGE ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  StartServer_Update () ; 
 TYPE_2__ s_startserver ; 

__attribute__((used)) static void StartServer_MapEvent( void* ptr, int event ) {
	if( event != QM_ACTIVATED) {
		return;
	}

	s_startserver.currentmap = (s_startserver.page*MAX_MAPSPERPAGE) + (((menucommon_s*)ptr)->id - ID_PICTURES);
	StartServer_Update();
}