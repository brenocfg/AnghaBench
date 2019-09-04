#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_7__** face; TYPE_1__* onnode; TYPE_3__** nodes; struct TYPE_10__** next; } ;
typedef  TYPE_2__ portal_t ;
struct TYPE_11__ {scalar_t__ planenum; int contents; TYPE_2__* portals; struct TYPE_11__** children; } ;
typedef  TYPE_3__ node_t ;
struct TYPE_12__ {struct TYPE_12__* next; } ;
struct TYPE_9__ {TYPE_7__* faces; } ;

/* Variables and functions */
 int CONTENTS_SOLID ; 
 TYPE_7__* FaceFromPortal (TYPE_2__*,int) ; 
 int /*<<< orphan*/  MergeNodeFaces (TYPE_3__*) ; 
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  SubdivideNodeFaces (TYPE_3__*) ; 
 int /*<<< orphan*/  c_nodefaces ; 
 int /*<<< orphan*/  nomerge ; 
 int /*<<< orphan*/  nosubdiv ; 

void MakeFaces_r (node_t *node)
{
	portal_t	*p;
	int			s;

	// recurse down to leafs
	if (node->planenum != PLANENUM_LEAF)
	{
		MakeFaces_r (node->children[0]);
		MakeFaces_r (node->children[1]);

		// merge together all visible faces on the node
		if (!nomerge)
			MergeNodeFaces (node);
		if (!nosubdiv)
			SubdivideNodeFaces (node);

		return;
	}

	// solid leafs never have visible faces
	if (node->contents & CONTENTS_SOLID)
		return;

	// see which portals are valid
	for (p=node->portals ; p ; p = p->next[s])
	{
		s = (p->nodes[1] == node);

		p->face[s] = FaceFromPortal (p, s);
		if (p->face[s])
		{
			c_nodefaces++;
			p->face[s]->next = p->onnode->faces;
			p->onnode->faces = p->face[s];
		}
	}
}