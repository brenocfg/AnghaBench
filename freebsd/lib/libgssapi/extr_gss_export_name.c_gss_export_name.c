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
struct _gss_name {int /*<<< orphan*/  gn_mn; } ;
struct _gss_mechanism_name {int /*<<< orphan*/  gmn_name; TYPE_1__* gmn_mech; } ;
typedef  scalar_t__ gss_name_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
struct TYPE_2__ {scalar_t__ (* gm_export_name ) (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_NAME_NOT_MN ; 
 struct _gss_mechanism_name* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _gss_buffer_zero (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

OM_uint32
gss_export_name(OM_uint32 *minor_status,
    const gss_name_t input_name,
    gss_buffer_t exported_name)
{
	struct _gss_name *name = (struct _gss_name *) input_name;
	struct _gss_mechanism_name *mn;

	_gss_buffer_zero(exported_name);

	/*
	 * If this name already has any attached MNs, export the first
	 * one, otherwise export based on the first mechanism in our
	 * list.
	 */
	mn = SLIST_FIRST(&name->gn_mn);
	if (!mn) {
		*minor_status = 0;
		return (GSS_S_NAME_NOT_MN);
	}

	return mn->gmn_mech->gm_export_name(minor_status,
	    mn->gmn_name, exported_name);
}