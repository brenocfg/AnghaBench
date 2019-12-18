#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numpoints; int /*<<< orphan*/ ** p; } ;
typedef  TYPE_1__ winding_t ;
struct TYPE_7__ {TYPE_3__** nodes; TYPE_1__* winding; struct TYPE_7__** next; } ;
typedef  TYPE_2__ portal_t ;
struct TYPE_8__ {scalar_t__ planenum; int cluster; TYPE_2__* portals; scalar_t__ opaque; struct TYPE_8__** children; } ;
typedef  TYPE_3__ node_t ;

/* Variables and functions */
 scalar_t__ PLANENUM_LEAF ; 
 scalar_t__ PortalPassable (TYPE_2__*) ; 
 int /*<<< orphan*/  WriteFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pf ; 

void WriteFaceFile_r( node_t *node ){
	int i, s;
	portal_t    *p;
	winding_t   *w;

	// decision node
	if ( node->planenum != PLANENUM_LEAF ) {
		WriteFaceFile_r( node->children[0] );
		WriteFaceFile_r( node->children[1] );
		return;
	}

	if ( node->opaque ) {
		return;
	}

	for ( p = node->portals ; p ; p = p->next[s] )
	{
		w = p->winding;
		s = ( p->nodes[1] == node );
		if ( w ) {
			if ( PortalPassable( p ) ) {
				continue;
			}
			// write out to the file

			if ( p->nodes[0] == node ) {
				fprintf( pf,"%i %i ",w->numpoints, p->nodes[0]->cluster );
				for ( i = 0 ; i < w->numpoints ; i++ )
				{
					fprintf( pf,"(" );
					WriteFloat( pf, w->p[i][0] );
					WriteFloat( pf, w->p[i][1] );
					WriteFloat( pf, w->p[i][2] );
					fprintf( pf,") " );
				}
				fprintf( pf,"\n" );
			}
			else
			{
				fprintf( pf,"%i %i ",w->numpoints, p->nodes[1]->cluster );
				for ( i = w->numpoints - 1; i >= 0; i-- )
				{
					fprintf( pf,"(" );
					WriteFloat( pf, w->p[i][0] );
					WriteFloat( pf, w->p[i][1] );
					WriteFloat( pf, w->p[i][2] );
					fprintf( pf,") " );
				}
				fprintf( pf,"\n" );
			}
		}
	}
}