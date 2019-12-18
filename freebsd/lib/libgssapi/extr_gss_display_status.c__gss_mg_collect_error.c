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
struct _gss_mech_switch {int dummy; } ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 struct _gss_mech_switch* _gss_find_mech_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gss_mg_error (struct _gss_mech_switch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
_gss_mg_collect_error(gss_OID mech, OM_uint32 maj, OM_uint32 min)
{
	struct _gss_mech_switch *m;

	m = _gss_find_mech_switch(mech);
	if (m != NULL)
		_gss_mg_error(m, maj, min);
}