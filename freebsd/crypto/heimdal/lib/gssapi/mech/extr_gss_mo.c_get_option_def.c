#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  gss_mo_desc ;
typedef  int /*<<< orphan*/  gss_const_OID ;
typedef  int /*<<< orphan*/  gss_buffer_t ;

/* Variables and functions */

__attribute__((used)) static int
get_option_def(int def, gss_const_OID mech, gss_mo_desc *mo, gss_buffer_t value)
{
    return def;
}