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
struct TYPE_4__ {scalar_t__ type; scalar_t__ floating; struct TYPE_4__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_FLOATING_CON ; 
 scalar_t__ CT_OUTPUT ; 
 scalar_t__ CT_WORKSPACE ; 
 scalar_t__ FLOATING_AUTO_ON ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

Con *con_inside_floating(Con *con) {
    assert(con != NULL);
    if (con->type == CT_FLOATING_CON)
        return con;

    if (con->floating >= FLOATING_AUTO_ON)
        return con->parent;

    if (con->type == CT_WORKSPACE || con->type == CT_OUTPUT)
        return NULL;

    return con_inside_floating(con->parent);
}