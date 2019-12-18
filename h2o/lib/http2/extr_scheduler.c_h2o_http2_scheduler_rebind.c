#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_9__ {struct TYPE_9__* _parent; int /*<<< orphan*/  _all_refs; } ;
struct TYPE_8__ {int weight; TYPE_2__ node; } ;
typedef  TYPE_1__ h2o_http2_scheduler_openref_t ;
typedef  TYPE_2__ h2o_http2_scheduler_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  do_rebind (TYPE_1__*,TYPE_2__*,int) ; 
 int h2o_http2_scheduler_is_open (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_linklist_is_empty (int /*<<< orphan*/ *) ; 

void h2o_http2_scheduler_rebind(h2o_http2_scheduler_openref_t *ref, h2o_http2_scheduler_node_t *new_parent, uint16_t weight,
                                int exclusive)
{
    assert(h2o_http2_scheduler_is_open(ref));
    assert(&ref->node != new_parent);
    assert(1 <= weight);
    assert(weight <= 257);

    /* do nothing if there'd be no change at all */
    if (ref->node._parent == new_parent && ref->weight == weight && !exclusive)
        return;

    ref->weight = weight;

    /* if new_parent is dependent to ref, make new_parent a sibling of ref before applying the final transition (see draft-16
       5.3.3) */
    if (!h2o_linklist_is_empty(&ref->node._all_refs)) {
        h2o_http2_scheduler_node_t *t;
        for (t = new_parent; t->_parent != NULL; t = t->_parent) {
            if (t->_parent == &ref->node) {
                /* quoting the spec: "The moved dependency retains its weight." */
                h2o_http2_scheduler_openref_t *new_parent_ref = (void *)new_parent;
                do_rebind(new_parent_ref, ref->node._parent, 0);
                break;
            }
        }
    }

    do_rebind(ref, new_parent, exclusive);
}