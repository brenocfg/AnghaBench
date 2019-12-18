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
struct TYPE_4__ {scalar_t__ type; scalar_t__ layout; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_FLOATING_CON ; 
 scalar_t__ CT_WORKSPACE ; 
 scalar_t__ L_STACKED ; 
 scalar_t__ L_TABBED ; 
 scalar_t__ con_is_leaf (TYPE_1__*) ; 

bool should_inset_con(Con *con, int children) {
    /* Don't inset floating containers and workspaces. */
    if (con->type == CT_FLOATING_CON || con->type == CT_WORKSPACE)
        return false;

    if (con_is_leaf(con))
        return true;

    return (con->layout == L_STACKED || con->layout == L_TABBED) && children > 0;
}