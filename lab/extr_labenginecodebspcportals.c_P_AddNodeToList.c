#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 TYPE_1__* p_firstnode ; 
 TYPE_1__* p_lastnode ; 

void P_AddNodeToList(node_t *node)
{
	node->next = NULL;
	if (p_lastnode) p_lastnode->next = node;
	else p_firstnode = node;
	p_lastnode = node;
}