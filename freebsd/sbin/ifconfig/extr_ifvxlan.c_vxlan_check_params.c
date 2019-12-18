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
struct TYPE_2__ {int vxlp_with; } ;

/* Variables and functions */
 int VXLAN_PARAM_WITH_LOCAL_ADDR4 ; 
 int VXLAN_PARAM_WITH_LOCAL_ADDR6 ; 
 int VXLAN_PARAM_WITH_REMOTE_ADDR4 ; 
 int VXLAN_PARAM_WITH_REMOTE_ADDR6 ; 
 int _LOCAL_ADDR46 ; 
 int _REMOTE_ADDR46 ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 TYPE_1__ params ; 

__attribute__((used)) static void
vxlan_check_params(void)
{

	if ((params.vxlp_with & _LOCAL_ADDR46) == _LOCAL_ADDR46)
		errx(1, "cannot specify both local IPv4 and IPv6 addresses");
	if ((params.vxlp_with & _REMOTE_ADDR46) == _REMOTE_ADDR46)
		errx(1, "cannot specify both remote IPv4 and IPv6 addresses");
	if ((params.vxlp_with & VXLAN_PARAM_WITH_LOCAL_ADDR4 &&
	     params.vxlp_with & VXLAN_PARAM_WITH_REMOTE_ADDR6) ||
	    (params.vxlp_with & VXLAN_PARAM_WITH_LOCAL_ADDR6 &&
	     params.vxlp_with & VXLAN_PARAM_WITH_REMOTE_ADDR4))
		errx(1, "cannot mix IPv4 and IPv6 addresses");
}