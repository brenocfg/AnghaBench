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
 scalar_t__ ParseEntity () ; 
 int /*<<< orphan*/  ParseFromMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bspEntData ; 
 int /*<<< orphan*/  bspEntDataSize ; 
 scalar_t__ numBSPEntities ; 
 scalar_t__ numEntities ; 

void ParseEntities( void ){
	numEntities = 0;
	ParseFromMemory( bspEntData, bspEntDataSize );
	while ( ParseEntity() ) ;

	/* ydnar: set number of bsp entities in case a map is loaded on top */
	numBSPEntities = numEntities;
}