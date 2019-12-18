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
struct mlx5_pagefault {int flags; } ;
typedef  enum mlx5_ib_pagefault_context { ____Placeholder_mlx5_ib_pagefault_context } mlx5_ib_pagefault_context ;

/* Variables and functions */
 int MLX5_PFAULT_REQUESTOR ; 
 int MLX5_PFAULT_WRITE ; 

__attribute__((used)) static inline enum mlx5_ib_pagefault_context
	mlx5_ib_get_pagefault_context(struct mlx5_pagefault *pagefault)
{
	return pagefault->flags & (MLX5_PFAULT_REQUESTOR | MLX5_PFAULT_WRITE);
}