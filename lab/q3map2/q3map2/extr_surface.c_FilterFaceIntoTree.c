#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_3__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;
typedef  int /*<<< orphan*/  mapDrawSurface_t ;

/* Variables and functions */
 int FilterWindingIntoTree_r (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WindingFromDrawSurf (int /*<<< orphan*/ *) ; 

int FilterFaceIntoTree( mapDrawSurface_t *ds, tree_t *tree ){
	winding_t   *w;
	int refs = 0;


	/* make a winding and filter it into the tree */
	w = WindingFromDrawSurf( ds );
	refs = FilterWindingIntoTree_r( w, ds, tree->headnode );

	/* return */
	return refs;
}