#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {float dist; int /*<<< orphan*/  normal; } ;
struct TYPE_19__ {scalar_t__ status; float radius; int leaf; TYPE_3__ plane; void* winding; int /*<<< orphan*/  origin; scalar_t__ portalflood; scalar_t__ portalvis; scalar_t__ removed; } ;
typedef  TYPE_4__ vportal_t ;
struct TYPE_20__ {float dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_5__ visPlane_t ;
struct TYPE_16__ {TYPE_5__ portalplane; } ;
struct TYPE_21__ {TYPE_2__* base; TYPE_1__ pstack_head; int /*<<< orphan*/  c_chains; } ;
typedef  TYPE_6__ threaddata_t ;
struct TYPE_22__ {int* numseperators; int* mightsee; int* freewindings; struct TYPE_22__* next; void* pass; void* source; TYPE_5__** seperators; TYPE_4__* portal; TYPE_3__ portalplane; scalar_t__ depth; TYPE_8__* leaf; } ;
typedef  TYPE_7__ pstack_t ;
struct TYPE_23__ {int numportals; TYPE_4__** portals; } ;
typedef  TYPE_8__ leaf_t ;
struct TYPE_17__ {int* portalvis; float radius; int /*<<< orphan*/  origin; } ;

/* Variables and functions */
 void* ClipToSeperators (void*,void*,void*,int /*<<< orphan*/ ,TYPE_7__*) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* VisChopWinding (void*,TYPE_7__*,TYPE_5__*) ; 
 TYPE_8__* leafs ; 
 int portallongs ; 
 TYPE_4__* portals ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ stat_done ; 
 int /*<<< orphan*/  vec3_origin ; 

void RecursiveLeafFlow( int leafnum, threaddata_t *thread, pstack_t *prevstack ){
	pstack_t stack;
	vportal_t   *p;
	visPlane_t backplane;
	leaf_t      *leaf;
	int i, j, n;
	long        *test, *might, *prevmight, *vis, more;
	int pnum;

	thread->c_chains++;

	leaf = &leafs[leafnum];
//	CheckStack (leaf, thread);

	prevstack->next = &stack;

	stack.next = NULL;
	stack.leaf = leaf;
	stack.portal = NULL;
	stack.depth = prevstack->depth + 1;

#ifdef SEPERATORCACHE
	stack.numseperators[0] = 0;
	stack.numseperators[1] = 0;
#endif

	might = (long *)stack.mightsee;
	vis = (long *)thread->base->portalvis;

	// check all portals for flowing into other leafs
	for ( i = 0; i < leaf->numportals; i++ )
	{
		p = leaf->portals[i];
		if ( p->removed ) {
			continue;
		}
		pnum = p - portals;

		/* MrE: portal trace debug code
		   {
		    int portaltrace[] = {13, 16, 17, 37};
		    pstack_t *s;

		    s = &thread->pstack_head;
		    for (j = 0; s->next && j < sizeof(portaltrace)/sizeof(int) - 1; j++, s = s->next)
		    {
		        if (s->portal->num != portaltrace[j])
		            break;
		    }
		    if (j >= sizeof(portaltrace)/sizeof(int) - 1)
		    {
		        if (p->num == portaltrace[j])
		            n = 0; //traced through all the portals
		    }
		   }
		 */

		if ( !( prevstack->mightsee[pnum >> 3] & ( 1 << ( pnum & 7 ) ) ) ) {
			continue;   // can't possibly see it
		}

		// if the portal can't see anything we haven't allready seen, skip it
		if ( p->status == stat_done ) {
			test = (long *)p->portalvis;
		}
		else
		{
			test = (long *)p->portalflood;
		}

		more = 0;
		prevmight = (long *)prevstack->mightsee;
		for ( j = 0 ; j < portallongs ; j++ )
		{
			might[j] = prevmight[j] & test[j];
			more |= ( might[j] & ~vis[j] );
		}

		if ( !more &&
			 ( thread->base->portalvis[pnum >> 3] & ( 1 << ( pnum & 7 ) ) ) ) { // can't see anything new
			continue;
		}

		// get plane of portal, point normal into the neighbor leaf
		stack.portalplane = p->plane;
		VectorSubtract( vec3_origin, p->plane.normal, backplane.normal );
		backplane.dist = -p->plane.dist;

//		c_portalcheck++;

		stack.portal = p;
		stack.next = NULL;
		stack.freewindings[0] = 1;
		stack.freewindings[1] = 1;
		stack.freewindings[2] = 1;

#if 1
		{
			float d;

			d = DotProduct( p->origin, thread->pstack_head.portalplane.normal );
			d -= thread->pstack_head.portalplane.dist;
			if ( d < -p->radius ) {
				continue;
			}
			else if ( d > p->radius ) {
				stack.pass = p->winding;
			}
			else
			{
				stack.pass = VisChopWinding( p->winding, &stack, &thread->pstack_head.portalplane );
				if ( !stack.pass ) {
					continue;
				}
			}
		}
#else
		stack.pass = VisChopWinding( p->winding, &stack, &thread->pstack_head.portalplane );
		if ( !stack.pass ) {
			continue;
		}
#endif


#if 1
		{
			float d;

			d = DotProduct( thread->base->origin, p->plane.normal );
			d -= p->plane.dist;
			//MrE: vis-bug fix
			//if (d > p->radius)
			if ( d > thread->base->radius ) {
				continue;
			}
			//MrE: vis-bug fix
			//if (d < -p->radius)
			else if ( d < -thread->base->radius ) {
				stack.source = prevstack->source;
			}
			else
			{
				stack.source = VisChopWinding( prevstack->source, &stack, &backplane );
				//FIXME: shouldn't we create a new source origin and radius for fast checks?
				if ( !stack.source ) {
					continue;
				}
			}
		}
#else
		stack.source = VisChopWinding( prevstack->source, &stack, &backplane );
		if ( !stack.source ) {
			continue;
		}
#endif

		if ( !prevstack->pass ) { // the second leaf can only be blocked if coplanar

			// mark the portal as visible
			thread->base->portalvis[pnum >> 3] |= ( 1 << ( pnum & 7 ) );

			RecursiveLeafFlow( p->leaf, thread, &stack );
			continue;
		}

#ifdef SEPERATORCACHE
		if ( stack.numseperators[0] ) {
			for ( n = 0; n < stack.numseperators[0]; n++ )
			{
				stack.pass = VisChopWinding( stack.pass, &stack, &stack.seperators[0][n] );
				if ( !stack.pass ) {
					break;      // target is not visible
				}
			}
			if ( n < stack.numseperators[0] ) {
				continue;
			}
		}
		else
		{
			stack.pass = ClipToSeperators( prevstack->source, prevstack->pass, stack.pass, qfalse, &stack );
		}
#else
		stack.pass = ClipToSeperators( stack.source, prevstack->pass, stack.pass, qfalse, &stack );
#endif
		if ( !stack.pass ) {
			continue;
		}

#ifdef SEPERATORCACHE
		if ( stack.numseperators[1] ) {
			for ( n = 0; n < stack.numseperators[1]; n++ )
			{
				stack.pass = VisChopWinding( stack.pass, &stack, &stack.seperators[1][n] );
				if ( !stack.pass ) {
					break;      // target is not visible
				}
			}
		}
		else
		{
			stack.pass = ClipToSeperators( prevstack->pass, prevstack->source, stack.pass, qtrue, &stack );
		}
#else
		stack.pass = ClipToSeperators( prevstack->pass, stack.source, stack.pass, qtrue, &stack );
#endif
		if ( !stack.pass ) {
			continue;
		}

		// mark the portal as visible
		thread->base->portalvis[pnum >> 3] |= ( 1 << ( pnum & 7 ) );

		// flow through it for real
		RecursiveLeafFlow( p->leaf, thread, &stack );
		//
		stack.next = NULL;
	}
}