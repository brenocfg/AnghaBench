#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  multilist_t ;
struct TYPE_2__ {int /*<<< orphan*/  dn_object; int /*<<< orphan*/  dn_objset; } ;
typedef  TYPE_1__ dnode_t ;

/* Variables and functions */
 unsigned int dnode_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int multilist_get_num_sublists (int /*<<< orphan*/ *) ; 

unsigned int
dnode_multilist_index_func(multilist_t *ml, void *obj)
{
	dnode_t *dn = obj;
	return (dnode_hash(dn->dn_objset, dn->dn_object) %
	    multilist_get_num_sublists(ml));
}