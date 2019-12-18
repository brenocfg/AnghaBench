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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mlx5_wqe_umr_klm_seg {int /*<<< orphan*/  address; void* mkey; void* byte_count; } ;
struct mlx5_qp {int dummy; } ;
struct ibv_mw_bind_info {int /*<<< orphan*/  addr; TYPE_1__* mr; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum ibv_mw_type { ____Placeholder_ibv_mw_type } ibv_mw_type ;
struct TYPE_2__ {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 void* htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_wqe_umr_klm_seg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_umr_data_seg(struct mlx5_qp *qp, enum ibv_mw_type type,
			     int32_t rkey, struct ibv_mw_bind_info *bind_info,
			     uint32_t qpn, void **seg, int *size)
{
	union {
		struct mlx5_wqe_umr_klm_seg	klm;
		uint8_t				reserved[64];
	} *data = *seg;

	data->klm.byte_count = htobe32(bind_info->length);
	data->klm.mkey = htobe32(bind_info->mr->lkey);
	data->klm.address = htobe64(bind_info->addr);

	memset(&data->klm + 1, 0, sizeof(data->reserved) -
	       sizeof(data->klm));

	*seg += sizeof(*data);
	*size += (sizeof(*data) / 16);
}