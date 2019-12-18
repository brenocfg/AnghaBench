#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; struct TYPE_4__* parent; int /*<<< orphan*/  deco_render_params; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_DOCKAREA ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_is_leaf (TYPE_1__*) ; 

void con_force_split_parents_redraw(Con *con) {
    Con *parent = con;

    while (parent != NULL && parent->type != CT_WORKSPACE && parent->type != CT_DOCKAREA) {
        if (!con_is_leaf(parent)) {
            FREE(parent->deco_render_params);
        }

        parent = parent->parent;
    }
}