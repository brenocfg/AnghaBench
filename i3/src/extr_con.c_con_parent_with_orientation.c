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
typedef  scalar_t__ orientation_t ;
struct TYPE_5__ {scalar_t__ type; struct TYPE_5__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_FLOATING_CON ; 
 scalar_t__ CT_OUTPUT ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 scalar_t__ con_orientation (TYPE_1__*) ; 

Con *con_parent_with_orientation(Con *con, orientation_t orientation) {
    DLOG("Searching for parent of Con %p with orientation %d\n", con, orientation);
    Con *parent = con->parent;
    if (parent->type == CT_FLOATING_CON)
        return NULL;
    while (con_orientation(parent) != orientation) {
        DLOG("Need to go one level further up\n");
        parent = parent->parent;
        /* Abort when we reach a floating con, or an output con */
        if (parent &&
            (parent->type == CT_FLOATING_CON ||
             parent->type == CT_OUTPUT ||
             (parent->parent && parent->parent->type == CT_OUTPUT)))
            parent = NULL;
        if (parent == NULL)
            break;
    }
    DLOG("Result: %p\n", parent);
    return parent;
}