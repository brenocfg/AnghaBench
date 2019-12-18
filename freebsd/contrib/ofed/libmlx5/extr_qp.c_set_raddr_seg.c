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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mlx5_wqe_raddr_seg {scalar_t__ reserved; int /*<<< orphan*/  rkey; int /*<<< orphan*/  raddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_raddr_seg(struct mlx5_wqe_raddr_seg *rseg,
				 uint64_t remote_addr, uint32_t rkey)
{
	rseg->raddr    = htobe64(remote_addr);
	rseg->rkey     = htobe32(rkey);
	rseg->reserved = 0;
}