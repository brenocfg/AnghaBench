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
typedef  int /*<<< orphan*/  gss_OID_set ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_NO_OID_SET ; 
 scalar_t__ GSS_S_COMPLETE ; 

OM_uint32 _gss_ntlm_indicate_mechs
(OM_uint32 * minor_status,
 gss_OID_set * mech_set
    )
{
    if (minor_status)
	*minor_status = 0;
    if (mech_set)
	*mech_set = GSS_C_NO_OID_SET;
    return GSS_S_COMPLETE;
}