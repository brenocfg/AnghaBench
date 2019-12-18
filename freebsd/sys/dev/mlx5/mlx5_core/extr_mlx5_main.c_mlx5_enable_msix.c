#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_eq_table {int num_comp_vectors; } ;
struct mlx5_priv {TYPE_1__* msix_arr; struct mlx5_eq_table eq_table; } ;
struct mlx5_core_dev {int msix_eqvec; int /*<<< orphan*/  pdev; struct mlx5_priv priv; } ;
struct TYPE_3__ {int entry; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_EQ_VEC_COMP_BASE ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_max_eq ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  num_ports ; 
 int pci_enable_msix_range (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 

__attribute__((used)) static int mlx5_enable_msix(struct mlx5_core_dev *dev)
{
	struct mlx5_priv *priv = &dev->priv;
	struct mlx5_eq_table *table = &priv->eq_table;
	int num_eqs = 1 << MLX5_CAP_GEN(dev, log_max_eq);
	int limit = dev->msix_eqvec;
	int nvec = MLX5_EQ_VEC_COMP_BASE;
	int i;

	if (limit > 0)
		nvec += limit;
	else
		nvec += MLX5_CAP_GEN(dev, num_ports) * num_online_cpus();

	if (nvec > num_eqs)
		nvec = num_eqs;
	if (nvec > 256)
		nvec = 256;	/* limit of firmware API */
	if (nvec <= MLX5_EQ_VEC_COMP_BASE)
		return -ENOMEM;

	priv->msix_arr = kzalloc(nvec * sizeof(*priv->msix_arr), GFP_KERNEL);

	for (i = 0; i < nvec; i++)
		priv->msix_arr[i].entry = i;

	nvec = pci_enable_msix_range(dev->pdev, priv->msix_arr,
				     MLX5_EQ_VEC_COMP_BASE + 1, nvec);
	if (nvec < 0)
		return nvec;

	table->num_comp_vectors = nvec - MLX5_EQ_VEC_COMP_BASE;
	return 0;
}