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
struct TYPE_4__ {scalar_t__ name; } ;
typedef  TYPE_1__ __cvmx_qlm_jtag_field_t ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_dprintf (char*,char const*) ; 
 TYPE_1__* cvmx_qlm_jtag_get_field () ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static const __cvmx_qlm_jtag_field_t *__cvmx_qlm_lookup_field(const char *name)
{
    const __cvmx_qlm_jtag_field_t *ptr = cvmx_qlm_jtag_get_field();
    while (ptr->name)
    {
        if (strcmp(name, ptr->name) == 0)
            return ptr;
        ptr++;
    }
    cvmx_dprintf("__cvmx_qlm_lookup_field: Illegal field name %s\n", name);
    return NULL;
}