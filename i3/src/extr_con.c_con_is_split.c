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
struct TYPE_4__ {int layout; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
#define  L_DOCKAREA 129 
#define  L_OUTPUT 128 
 scalar_t__ con_is_leaf (TYPE_1__*) ; 

bool con_is_split(Con *con) {
    if (con_is_leaf(con))
        return false;

    switch (con->layout) {
        case L_DOCKAREA:
        case L_OUTPUT:
            return false;

        default:
            return true;
    }
}