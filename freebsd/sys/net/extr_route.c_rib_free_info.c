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
struct rt_addrinfo {int /*<<< orphan*/  rti_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  if_rele (int /*<<< orphan*/ ) ; 

void
rib_free_info(struct rt_addrinfo *info)
{

	if_rele(info->rti_ifp);
}