#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t children_count; size_t children_capacity; struct TYPE_7__** children; } ;
typedef  TYPE_1__ IjkMediaMeta ;

/* Variables and functions */
 size_t IJK_META_INIT_CAPACITY ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__**,TYPE_1__**,int) ; 

void ijkmeta_append_child_l(IjkMediaMeta *meta, IjkMediaMeta *child)
{
    if (!meta || !child)
        return;

    if (!meta->children) {
        meta->children = (IjkMediaMeta **)calloc(IJK_META_INIT_CAPACITY, sizeof(IjkMediaMeta *));
        if (!meta->children)
            return;
        meta->children_count    = 0;
        meta->children_capacity = IJK_META_INIT_CAPACITY;
    } else if (meta->children_count >= meta->children_capacity) {
        size_t new_capacity = meta->children_capacity * 2;
        IjkMediaMeta **new_children = (IjkMediaMeta **)calloc(new_capacity, sizeof(IjkMediaMeta *));
        if (!new_children)
            return;

        memcpy(new_children, meta->children, meta->children_capacity * sizeof(IjkMediaMeta *));
        free(meta->children);
        meta->children          = new_children;
        meta->children_capacity = new_capacity;
    }

    meta->children[meta->children_count] = child;
    meta->children_count++;
}