#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_8__ {TYPE_3__* eq; } ;
struct mlx4_priv {TYPE_4__ eq_table; } ;
struct TYPE_5__ {int num_comp_vectors; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct TYPE_6__ {int /*<<< orphan*/  ports; } ;
struct TYPE_7__ {TYPE_2__ actv_ports; } ;

/* Variables and functions */
 int MLX4_CQ_TO_EQ_VECTOR (int) ; 
 int MLX4_EQ_ASYNC ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

bool mlx4_is_eq_vector_valid(struct mlx4_dev *dev, u8 port, int vector)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	vector = MLX4_CQ_TO_EQ_VECTOR(vector);
	if (vector < 0 || (vector >= dev->caps.num_comp_vectors + 1) ||
	    (vector == MLX4_EQ_ASYNC))
		return false;

	return test_bit(port - 1, priv->eq_table.eq[vector].actv_ports.ports);
}