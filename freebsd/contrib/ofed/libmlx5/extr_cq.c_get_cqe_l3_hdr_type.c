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
typedef  int uint8_t ;
struct mlx5_cqe64 {int l4_hdr_type_etc; } ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t get_cqe_l3_hdr_type(struct mlx5_cqe64 *cqe)
{
	return (cqe->l4_hdr_type_etc >> 2) & 0x3;
}