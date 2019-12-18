#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct _gss_mechanism_name {TYPE_1__* gmn_mech; int /*<<< orphan*/  gmn_mech_oid; int /*<<< orphan*/  gmn_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* gm_pname_to_uid ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSS_S_UNAVAILABLE ; 
 int /*<<< orphan*/  _gss_mg_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OM_uint32
mech_pname_to_uid(OM_uint32 *minor_status,
                  struct _gss_mechanism_name *mn,
                  uid_t *uidp)
{
    OM_uint32 major_status = GSS_S_UNAVAILABLE;

    *minor_status = 0;

    if (mn->gmn_mech->gm_pname_to_uid == NULL)
        return GSS_S_UNAVAILABLE;

    major_status = mn->gmn_mech->gm_pname_to_uid(minor_status,
                                                 mn->gmn_name,
                                                 mn->gmn_mech_oid,
                                                 uidp);
    if (GSS_ERROR(major_status))
        _gss_mg_error(mn->gmn_mech, major_status, *minor_status);

    return major_status;
}