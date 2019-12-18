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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ GSS_C_QOP_DEFAULT ; 

const char *
_rpc_gss_num_to_qop(const char *mech, u_int num)
{

	if (num == GSS_C_QOP_DEFAULT)
		return "default";

	return (NULL);
}