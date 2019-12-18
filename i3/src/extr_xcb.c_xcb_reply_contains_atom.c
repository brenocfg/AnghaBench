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
struct TYPE_5__ {int format; } ;
typedef  TYPE_1__ xcb_get_property_reply_t ;
typedef  scalar_t__ xcb_atom_t ;

/* Variables and functions */
 scalar_t__* xcb_get_property_value (TYPE_1__*) ; 
 int xcb_get_property_value_length (TYPE_1__*) ; 

bool xcb_reply_contains_atom(xcb_get_property_reply_t *prop, xcb_atom_t atom) {
    if (prop == NULL || xcb_get_property_value_length(prop) == 0)
        return false;

    xcb_atom_t *atoms;
    if ((atoms = xcb_get_property_value(prop)) == NULL)
        return false;

    for (int i = 0; i < xcb_get_property_value_length(prop) / (prop->format / 8); i++)
        if (atoms[i] == atom)
            return true;

    return false;
}