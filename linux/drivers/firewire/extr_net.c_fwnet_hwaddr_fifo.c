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
struct TYPE_2__ {int /*<<< orphan*/  fifo_lo; int /*<<< orphan*/  fifo_hi; } ;
union fwnet_hwaddr {TYPE_1__ uc; } ;
typedef  int u64 ;
typedef  int __u64 ;

/* Variables and functions */
 scalar_t__ get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __u64 fwnet_hwaddr_fifo(union fwnet_hwaddr *ha)
{
	return (u64)get_unaligned_be16(&ha->uc.fifo_hi) << 32
	       | get_unaligned_be32(&ha->uc.fifo_lo);
}