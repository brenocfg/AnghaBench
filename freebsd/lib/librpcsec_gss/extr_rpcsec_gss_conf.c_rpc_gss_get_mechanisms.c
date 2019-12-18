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

/* Variables and functions */
 int /*<<< orphan*/  _rpc_gss_load_mech () ; 
 char const** mech_names ; 

const char **
rpc_gss_get_mechanisms(void)
{

	_rpc_gss_load_mech();
	return (mech_names);
}