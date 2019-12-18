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
typedef  int u32 ;
struct mlx5_cqe64 {int /*<<< orphan*/  sop_drop_qpn; } ;

/* Variables and functions */
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_equal_rsn(struct mlx5_cqe64 *cqe64, u32 rsn)
{
	return rsn == (ntohl(cqe64->sop_drop_qpn) & 0xffffff);
}