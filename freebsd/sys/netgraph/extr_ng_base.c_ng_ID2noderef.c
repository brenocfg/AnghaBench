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
typedef  scalar_t__ node_p ;
typedef  int /*<<< orphan*/  ng_ID_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDHASH_RLOCK () ; 
 int /*<<< orphan*/  IDHASH_RUNLOCK () ; 
 int /*<<< orphan*/  NG_IDHASH_FIND (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NG_NODE_REF (scalar_t__) ; 

__attribute__((used)) static node_p
ng_ID2noderef(ng_ID_t ID)
{
	node_p node;

	IDHASH_RLOCK();
	NG_IDHASH_FIND(ID, node);
	if (node)
		NG_NODE_REF(node);
	IDHASH_RUNLOCK();
	return(node);
}