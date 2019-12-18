#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct _gss_name* elements; } ;
struct _gss_name {int /*<<< orphan*/  gn_value; int /*<<< orphan*/  gmn_name; TYPE_2__* gmn_mech; int /*<<< orphan*/  gn_mn; TYPE_1__ gn_type; } ;
struct _gss_mechanism_name {int /*<<< orphan*/  gn_value; int /*<<< orphan*/  gmn_name; TYPE_2__* gmn_mech; int /*<<< orphan*/  gn_mn; TYPE_1__ gn_type; } ;
typedef  scalar_t__ gss_name_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* gm_release_name ) (scalar_t__*,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_C_NO_NAME ; 
 scalar_t__ GSS_S_COMPLETE ; 
 struct _gss_name* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct _gss_name*) ; 
 int /*<<< orphan*/  gmn_link ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*,int /*<<< orphan*/ *) ; 

OM_uint32
gss_release_name(OM_uint32 *minor_status,
    gss_name_t *input_name)
{
	struct _gss_name *name = (struct _gss_name *) *input_name;

	*minor_status = 0;
	if (name) {
		if (name->gn_type.elements)
			free(name->gn_type.elements);
		while (SLIST_FIRST(&name->gn_mn)) {
			struct _gss_mechanism_name *mn;
			mn = SLIST_FIRST(&name->gn_mn);
			SLIST_REMOVE_HEAD(&name->gn_mn, gmn_link);
			mn->gmn_mech->gm_release_name(minor_status,
			    &mn->gmn_name);
			free(mn);
		}
		gss_release_buffer(minor_status, &name->gn_value);
		free(name);
		*input_name = GSS_C_NO_NAME;
	}
	return (GSS_S_COMPLETE);
}