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
struct mlx4_wqe_inline_seg {int /*<<< orphan*/  byte_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void add_zero_len_inline(void *wqe)
{
	struct mlx4_wqe_inline_seg *inl = wqe;
	memset(wqe, 0, 16);
	inl->byte_count = cpu_to_be32(1U << 31);
}