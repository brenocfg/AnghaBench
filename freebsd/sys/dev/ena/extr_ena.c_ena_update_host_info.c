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
typedef  scalar_t__ uint32_t ;
struct ena_admin_host_info {scalar_t__* supported_network_features; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 scalar_t__ if_getcapabilities (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ena_update_host_info(struct ena_admin_host_info *host_info, if_t ifp)
{

	host_info->supported_network_features[0] =
	    (uint32_t)if_getcapabilities(ifp);
}