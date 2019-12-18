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
typedef  int /*<<< orphan*/  u8 ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int WARN_ON (int) ; 
 int /*<<< orphan*/  rdma_cap_ib_mad (struct ib_device const*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_max_mad_size (struct ib_device const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_immutable(const struct ib_device *dev, u8 port)
{
	return WARN_ON(!rdma_cap_ib_mad(dev, port) &&
			    rdma_max_mad_size(dev, port) != 0);
}