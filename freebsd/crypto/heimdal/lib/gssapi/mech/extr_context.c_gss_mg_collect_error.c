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
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/ * __gss_get_mechanism (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gss_mg_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gss_mg_collect_error(gss_OID mech, OM_uint32 maj, OM_uint32 min)
{
    gssapi_mech_interface m = __gss_get_mechanism(mech);
    if (m == NULL)
	return;
    _gss_mg_error(m, maj, min);
}