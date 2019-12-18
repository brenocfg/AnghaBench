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
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;

/* Variables and functions */
#define  IB_GID_TYPE_ROCE 129 
#define  IB_GID_TYPE_ROCE_UDP_ENCAP 128 
 int /*<<< orphan*/  MLX4_QPC_ROCE_MODE_1 ; 
 int /*<<< orphan*/  MLX4_QPC_ROCE_MODE_2 ; 
 int /*<<< orphan*/  MLX4_QPC_ROCE_MODE_UNDEFINED ; 

__attribute__((used)) static u8 gid_type_to_qpc(enum ib_gid_type gid_type)
{
	switch (gid_type) {
	case IB_GID_TYPE_ROCE:
		return MLX4_QPC_ROCE_MODE_1;
	case IB_GID_TYPE_ROCE_UDP_ENCAP:
		return MLX4_QPC_ROCE_MODE_2;
	default:
		return MLX4_QPC_ROCE_MODE_UNDEFINED;
	}
}