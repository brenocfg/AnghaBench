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
struct TYPE_5__ {TYPE_1__* pack; struct TYPE_5__* next; } ;
typedef  TYPE_2__ searchpath_t ;
struct TYPE_4__ {int referenced; } ;

/* Variables and functions */
 TYPE_2__* fs_searchpaths ; 

void FS_ClearPakReferences( int flags ) {
	searchpath_t *search;

	if ( !flags ) {
		flags = -1;
	}
	for ( search = fs_searchpaths; search; search = search->next ) {
		// is the element a pak file and has it been referenced?
		if ( search->pack ) {
			search->pack->referenced &= ~flags;
		}
	}
}