#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ numnodes; int /*<<< orphan*/ * nodes; struct TYPE_3__* next; } ;
typedef  TYPE_1__ tmp_nodebuf_t ;
typedef  int /*<<< orphan*/  tmp_node_t ;
struct TYPE_4__ {TYPE_1__* nodebuffer; int /*<<< orphan*/  numnodes; } ;

/* Variables and functions */
 scalar_t__ GetClearedMemory (int) ; 
 scalar_t__ NODEBUF_SIZE ; 
 TYPE_2__ tmpaasworld ; 

tmp_node_t *AAS_AllocTmpNode(void)
{
	tmp_nodebuf_t *nodebuf;

	if (!tmpaasworld.nodebuffer ||
			tmpaasworld.nodebuffer->numnodes >= NODEBUF_SIZE)
	{
		nodebuf = (tmp_nodebuf_t *) GetClearedMemory(sizeof(tmp_nodebuf_t));
		nodebuf->next = tmpaasworld.nodebuffer;
		nodebuf->numnodes = 0;
		tmpaasworld.nodebuffer = nodebuf;
	} //end if
	tmpaasworld.numnodes++;
	return &tmpaasworld.nodebuffer->nodes[tmpaasworld.nodebuffer->numnodes++];
}