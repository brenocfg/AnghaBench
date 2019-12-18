#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* gssapi_mech_interface ;
typedef  int /*<<< orphan*/  gss_OID_set ;
struct TYPE_5__ {size_t gm_mo_num; TYPE_1__* gm_mo; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  option; } ;
typedef  int OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  gss_add_oid_set_member (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_all_mo(gssapi_mech_interface m, gss_OID_set *options, OM_uint32 mask)
{
    OM_uint32 minor;
    size_t n;

    for (n = 0; n < m->gm_mo_num; n++)
	if ((m->gm_mo[n].flags & mask) == mask)
	    gss_add_oid_set_member(&minor, m->gm_mo[n].option, options);
}