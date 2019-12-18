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
struct if_clone {int dummy; } ;

/* Variables and functions */
 int TUN_L2 ; 
 scalar_t__ tuntap_name2info (char const*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
tun_clone_match(struct if_clone *ifc, const char *name)
{
	int tunflags;

	if (tuntap_name2info(name, NULL, &tunflags) == 0) {
		if ((tunflags & TUN_L2) == 0)
			return (1);
	}

	return (0);
}