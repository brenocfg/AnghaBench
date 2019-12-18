#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; TYPE_1__* parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  focus_head; int /*<<< orphan*/  nodes_head; int /*<<< orphan*/  floating_head; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 scalar_t__ CT_FLOATING_CON ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_force_split_parents_redraw (TYPE_2__*) ; 
 int /*<<< orphan*/  floating_windows ; 
 int /*<<< orphan*/  focused ; 
 int /*<<< orphan*/  nodes ; 

void con_detach(Con *con) {
    con_force_split_parents_redraw(con);
    if (con->type == CT_FLOATING_CON) {
        TAILQ_REMOVE(&(con->parent->floating_head), con, floating_windows);
        TAILQ_REMOVE(&(con->parent->focus_head), con, focused);
    } else {
        TAILQ_REMOVE(&(con->parent->nodes_head), con, nodes);
        TAILQ_REMOVE(&(con->parent->focus_head), con, focused);
    }
}