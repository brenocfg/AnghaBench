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
typedef  int qboolean ;
struct TYPE_3__ {int /*<<< orphan*/ * nodes; int /*<<< orphan*/  onnode; } ;
typedef  TYPE_1__ portal_t ;

/* Variables and functions */
 int CONTENTS_DETAIL ; 
 int CONTENTS_Q2TRANSLUCENT ; 
 int CONTENTS_SOLID ; 
 int ClusterContents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VisibleContents (int) ; 

qboolean Portal_VisFlood (portal_t *p)
{
	int		c1, c2;

	if (!p->onnode)
		return false;	// to global outsideleaf

	c1 = ClusterContents(p->nodes[0]);
	c2 = ClusterContents(p->nodes[1]);

	if (!VisibleContents (c1^c2))
		return true;

	if (c1 & (CONTENTS_Q2TRANSLUCENT|CONTENTS_DETAIL))
		c1 = 0;
	if (c2 & (CONTENTS_Q2TRANSLUCENT|CONTENTS_DETAIL))
		c2 = 0;

	if ( (c1|c2) & CONTENTS_SOLID )
		return false;		// can't see through solid

	if (! (c1 ^ c2))
		return true;		// identical on both sides

	if (!VisibleContents (c1^c2))
		return true;
	return false;
}