#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ orientation_t ;
typedef  scalar_t__ direction_t ;
struct TYPE_9__ {scalar_t__ type; scalar_t__ layout; struct TYPE_9__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_FLOATING_CON ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 scalar_t__ D_LEFT ; 
 scalar_t__ D_UP ; 
 scalar_t__ L_STACKED ; 
 scalar_t__ L_TABBED ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_PREV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ const con_orientation (TYPE_1__*) ; 
 int /*<<< orphan*/  nodes ; 
 int /*<<< orphan*/  nodes_head ; 
 scalar_t__ orientation_from_direction (scalar_t__) ; 

bool resize_find_tiling_participants(Con **current, Con **other, direction_t direction, bool both_sides) {
    DLOG("Find two participants for resizing container=%p in direction=%i\n", other, direction);
    Con *first = *current;
    Con *second = NULL;
    if (first == NULL) {
        DLOG("Current container is NULL, aborting.\n");
        return false;
    }

    /* Go up in the tree and search for a container to resize */
    const orientation_t search_orientation = orientation_from_direction(direction);
    const bool dir_backwards = (direction == D_UP || direction == D_LEFT);
    while (first->type != CT_WORKSPACE &&
           first->type != CT_FLOATING_CON &&
           second == NULL) {
        /* get the appropriate first container with the matching
         * orientation (skip stacked/tabbed cons) */
        if ((con_orientation(first->parent) != search_orientation) ||
            (first->parent->layout == L_STACKED) ||
            (first->parent->layout == L_TABBED)) {
            first = first->parent;
            continue;
        }

        /* get the counterpart for this resizement */
        if (dir_backwards) {
            second = TAILQ_PREV(first, nodes_head, nodes);
            if (second == NULL && both_sides == true) {
                second = TAILQ_NEXT(first, nodes);
            }
        } else {
            second = TAILQ_NEXT(first, nodes);
            if (second == NULL && both_sides == true) {
                second = TAILQ_PREV(first, nodes_head, nodes);
            }
        }

        if (second == NULL) {
            DLOG("No second container in this direction found, trying to look further up in the tree...\n");
            first = first->parent;
        }
    }

    DLOG("Found participants: first=%p and second=%p.\n", first, second);
    *current = first;
    *other = second;
    if (first == NULL || second == NULL) {
        DLOG("Could not find two participants for this resize request.\n");
        return false;
    }

    return true;
}