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
struct mlx4_cq {int cons_index; int /*<<< orphan*/ * set_ci_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  htobe32 (int) ; 

__attribute__((used)) static inline void mlx4_update_cons_index(struct mlx4_cq *cq)
{
	*cq->set_ci_db = htobe32(cq->cons_index & 0xffffff);
}