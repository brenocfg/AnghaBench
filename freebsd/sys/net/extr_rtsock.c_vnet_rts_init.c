#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nh_qlimit; } ;

/* Variables and functions */
 scalar_t__ IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 scalar_t__ TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  netisr_register (TYPE_1__*) ; 
 int /*<<< orphan*/  netisr_register_vnet (TYPE_1__*) ; 
 TYPE_1__ rtsock_nh ; 

__attribute__((used)) static void
vnet_rts_init(void)
{
	int tmp;

	if (IS_DEFAULT_VNET(curvnet)) {
		if (TUNABLE_INT_FETCH("net.route.netisr_maxqlen", &tmp))
			rtsock_nh.nh_qlimit = tmp;
		netisr_register(&rtsock_nh);
	}
#ifdef VIMAGE
	 else
		netisr_register_vnet(&rtsock_nh);
#endif
}