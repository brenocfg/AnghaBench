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
typedef  int /*<<< orphan*/ * gssapi_mech_interface ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_mech ; 

gssapi_mech_interface
__gss_krb5_initialize(void)
{
    return &krb5_mech;
}