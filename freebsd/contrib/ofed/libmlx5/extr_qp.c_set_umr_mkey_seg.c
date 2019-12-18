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
typedef  int uint32_t ;
struct mlx5_wqe_mkey_context_seg {scalar_t__ free; void* len; void* start_addr; int /*<<< orphan*/  access_flags; int /*<<< orphan*/  qpn_mkey; } ;
struct mlx5_qp {int dummy; } ;
struct ibv_mw_bind_info {int mw_access_flags; scalar_t__ length; scalar_t__ addr; } ;
typedef  int int32_t ;
typedef  enum ibv_mw_type { ____Placeholder_ibv_mw_type } ibv_mw_type ;

/* Variables and functions */
 int IBV_ACCESS_LOCAL_WRITE ; 
 int IBV_ACCESS_REMOTE_ATOMIC ; 
 int IBV_ACCESS_REMOTE_READ ; 
 int IBV_ACCESS_REMOTE_WRITE ; 
 int IBV_ACCESS_ZERO_BASED ; 
 int IBV_MW_TYPE_1 ; 
 int /*<<< orphan*/  MLX5_WQE_MKEY_CONTEXT_ACCESS_FLAGS_ATOMIC ; 
 int /*<<< orphan*/  MLX5_WQE_MKEY_CONTEXT_ACCESS_FLAGS_LOCAL_WRITE ; 
 int /*<<< orphan*/  MLX5_WQE_MKEY_CONTEXT_ACCESS_FLAGS_REMOTE_READ ; 
 int /*<<< orphan*/  MLX5_WQE_MKEY_CONTEXT_ACCESS_FLAGS_REMOTE_WRITE ; 
 scalar_t__ MLX5_WQE_MKEY_CONTEXT_FREE ; 
 int /*<<< orphan*/  htobe32 (int) ; 
 void* htobe64 (scalar_t__) ; 

__attribute__((used)) static void set_umr_mkey_seg(struct mlx5_qp *qp, enum ibv_mw_type type,
			     int32_t rkey, struct ibv_mw_bind_info *bind_info,
			     uint32_t qpn, void **seg, int *size)
{
	struct mlx5_wqe_mkey_context_seg	*mkey = *seg;

	mkey->qpn_mkey = htobe32((rkey & 0xFF) |
				   ((type == IBV_MW_TYPE_1 || !bind_info->length) ?
				    0xFFFFFF00 : qpn << 8));
	if (bind_info->length) {
		/* Local read is set in kernel */
		mkey->access_flags = 0;
		mkey->free = 0;
		if (bind_info->mw_access_flags & IBV_ACCESS_LOCAL_WRITE)
			mkey->access_flags |=
				MLX5_WQE_MKEY_CONTEXT_ACCESS_FLAGS_LOCAL_WRITE;
		if (bind_info->mw_access_flags & IBV_ACCESS_REMOTE_WRITE)
			mkey->access_flags |=
				MLX5_WQE_MKEY_CONTEXT_ACCESS_FLAGS_REMOTE_WRITE;
		if (bind_info->mw_access_flags & IBV_ACCESS_REMOTE_READ)
			mkey->access_flags |=
				MLX5_WQE_MKEY_CONTEXT_ACCESS_FLAGS_REMOTE_READ;
		if (bind_info->mw_access_flags & IBV_ACCESS_REMOTE_ATOMIC)
			mkey->access_flags |=
				MLX5_WQE_MKEY_CONTEXT_ACCESS_FLAGS_ATOMIC;
		if (bind_info->mw_access_flags & IBV_ACCESS_ZERO_BASED)
			mkey->start_addr = 0;
		else
			mkey->start_addr = htobe64(bind_info->addr);
		mkey->len = htobe64(bind_info->length);
	} else {
		mkey->free = MLX5_WQE_MKEY_CONTEXT_FREE;
	}

	*seg += sizeof(struct mlx5_wqe_mkey_context_seg);
	*size += (sizeof(struct mlx5_wqe_mkey_context_seg) / 16);
}