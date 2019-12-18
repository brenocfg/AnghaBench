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
struct TYPE_5__ {scalar_t__ name; scalar_t__ materialRef; scalar_t__ numAnimations; } ;
struct TYPE_4__ {int currentObject; TYPE_2__* objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  ConcatenateObjects (TYPE_2__*,TYPE_2__*) ; 
 TYPE_1__ ase ; 
 scalar_t__ strstr (scalar_t__,char*) ; 

__attribute__((used)) static void CollapseObjects( void ){
	int i;
	int numObjects = ase.currentObject;

	for ( i = 0; i < numObjects; i++ )
	{
		int j;

		// skip tags
		if ( strstr( ase.objects[i].name, "tag" ) == ase.objects[i].name ) {
			continue;
		}

		if ( !ase.objects[i].numAnimations ) {
			continue;
		}

		for ( j = i + 1; j < numObjects; j++ )
		{
			if ( strstr( ase.objects[j].name, "tag" ) == ase.objects[j].name ) {
				continue;
			}
			if ( ase.objects[i].materialRef == ase.objects[j].materialRef ) {
				if ( ase.objects[j].numAnimations ) {
					ConcatenateObjects( &ase.objects[i], &ase.objects[j] );
				}
			}
		}
	}
}