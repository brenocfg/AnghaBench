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
struct roff_node {scalar_t__ type; scalar_t__ end; int flags; struct roff_node* parent; } ;

/* Variables and functions */
 scalar_t__ ENDBODY_NOT ; 
 int NODE_BROKEN ; 
 int NODE_VALID ; 
 scalar_t__ ROFFT_BLOCK ; 
 scalar_t__ ROFFT_BODY ; 
 scalar_t__ ROFFT_HEAD ; 

__attribute__((used)) static void
break_intermediate(struct roff_node *n, struct roff_node *breaker)
{
	if (n != breaker &&
	    n->type != ROFFT_BLOCK && n->type != ROFFT_HEAD &&
	    (n->type != ROFFT_BODY || n->end != ENDBODY_NOT))
		n = n->parent;
	while (n != breaker) {
		if ( ! (n->flags & NODE_VALID))
			n->flags |= NODE_BROKEN;
		n = n->parent;
	}
}