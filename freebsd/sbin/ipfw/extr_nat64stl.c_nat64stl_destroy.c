#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  oh ;
struct TYPE_3__ {int /*<<< orphan*/  opheader; int /*<<< orphan*/  ntlv; } ;
typedef  TYPE_1__ ipfw_obj_header ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  IP_FW_NAT64STL_DESTROY ; 
 scalar_t__ do_set3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nat64stl_fill_ntlv (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nat64stl_destroy(const char *name, uint8_t set)
{
	ipfw_obj_header oh;

	memset(&oh, 0, sizeof(oh));
	nat64stl_fill_ntlv(&oh.ntlv, name, set);
	if (do_set3(IP_FW_NAT64STL_DESTROY, &oh.opheader, sizeof(oh)) != 0)
		err(EX_OSERR, "failed to destroy nat instance %s", name);
}