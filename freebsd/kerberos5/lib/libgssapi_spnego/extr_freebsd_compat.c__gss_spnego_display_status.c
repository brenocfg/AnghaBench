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
typedef  int /*<<< orphan*/  gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_S_FAILURE ; 

OM_uint32 _gss_spnego_display_status
           (OM_uint32 * minor_status,
            OM_uint32 status_value,
            int status_type,
            const gss_OID mech_type,
            OM_uint32 * message_context,
            gss_buffer_t status_string
           )
{
    return GSS_S_FAILURE;
}