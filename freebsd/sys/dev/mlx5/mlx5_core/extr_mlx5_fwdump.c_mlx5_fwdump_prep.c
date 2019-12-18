#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u32 ;
struct mlx5_crspace_regmap {int dummy; } ;
struct mlx5_core_dev {int vsc_addr; int dump_size; int dump_valid; int dump_copyout; int /*<<< orphan*/ * dump_data; TYPE_3__* dump_rege; TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {scalar_t__ addr; int /*<<< orphan*/  cnt; } ;
struct TYPE_5__ {int /*<<< orphan*/  bsddev; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MLX5_VSC_ADDR_OFFSET ; 
 scalar_t__ MLX5_VSC_DATA_OFFSET ; 
 int /*<<< orphan*/  MLX5_VSC_DOMAIN_SCAN_CRSPACE ; 
 scalar_t__ MLX5_VSC_GET (int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_VSC_SET (int,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_MLX5_DUMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  address ; 
 int /*<<< orphan*/  free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 int mlx5_fwdump_getsize (TYPE_3__*) ; 
 int mlx5_vsc_find_cap (struct mlx5_core_dev*) ; 
 int mlx5_vsc_lock (struct mlx5_core_dev*) ; 
 int mlx5_vsc_set_space (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_vsc_unlock (struct mlx5_core_dev*) ; 
 int mlx5_vsc_wait_on_flag (struct mlx5_core_dev*,int) ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 

void
mlx5_fwdump_prep(struct mlx5_core_dev *mdev)
{
	device_t dev;
	int error, vsc_addr;
	unsigned i, sz;
	u32 addr, in, out, next_addr;

	mdev->dump_data = NULL;
	error = mlx5_vsc_find_cap(mdev);
	if (error != 0) {
		/* Inability to create a firmware dump is not fatal. */
		mlx5_core_warn(mdev,
		    "Failed to find vendor-specific capability, error %d\n",
		    error);
		return;
	}
	error = mlx5_vsc_lock(mdev);
	if (error != 0)
		return;
	error = mlx5_vsc_set_space(mdev, MLX5_VSC_DOMAIN_SCAN_CRSPACE);
	if (error != 0) {
		mlx5_core_warn(mdev, "VSC scan space is not supported\n");
		goto unlock_vsc;
	}
	dev = mdev->pdev->dev.bsddev;
	vsc_addr = mdev->vsc_addr;
	if (vsc_addr == 0) {
		mlx5_core_warn(mdev, "Cannot read VSC, no address\n");
		goto unlock_vsc;
	}

	in = 0;
	for (sz = 1, addr = 0;;) {
		MLX5_VSC_SET(vsc_addr, &in, address, addr);
		pci_write_config(dev, vsc_addr + MLX5_VSC_ADDR_OFFSET, in, 4);
		error = mlx5_vsc_wait_on_flag(mdev, 1);
		if (error != 0) {
			mlx5_core_warn(mdev,
		    "Failed waiting for read complete flag, error %d addr %#x\n",
			    error, addr);
			goto unlock_vsc;
		}
		pci_read_config(dev, vsc_addr + MLX5_VSC_DATA_OFFSET, 4);
		out = pci_read_config(dev, vsc_addr + MLX5_VSC_ADDR_OFFSET, 4);
		next_addr = MLX5_VSC_GET(vsc_addr, &out, address);
		if (next_addr == 0 || next_addr == addr)
			break;
		if (next_addr != addr + 4)
			sz++;
		addr = next_addr;
	}
	mdev->dump_rege = malloc(sz * sizeof(struct mlx5_crspace_regmap),
	    M_MLX5_DUMP, M_WAITOK | M_ZERO);

	for (i = 0, addr = 0;;) {
		MPASS(i < sz);
		mdev->dump_rege[i].cnt++;
		MLX5_VSC_SET(vsc_addr, &in, address, addr);
		pci_write_config(dev, vsc_addr + MLX5_VSC_ADDR_OFFSET, in, 4);
		error = mlx5_vsc_wait_on_flag(mdev, 1);
		if (error != 0) {
			mlx5_core_warn(mdev,
		    "Failed waiting for read complete flag, error %d addr %#x\n",
			    error, addr);
			free(mdev->dump_rege, M_MLX5_DUMP);
			mdev->dump_rege = NULL;
			goto unlock_vsc;
		}
		pci_read_config(dev, vsc_addr + MLX5_VSC_DATA_OFFSET, 4);
		out = pci_read_config(dev, vsc_addr + MLX5_VSC_ADDR_OFFSET, 4);
		next_addr = MLX5_VSC_GET(vsc_addr, &out, address);
		if (next_addr == 0 || next_addr == addr)
			break;
		if (next_addr != addr + 4)
			mdev->dump_rege[++i].addr = next_addr;
		addr = next_addr;
	}
	KASSERT(i + 1 == sz,
	    ("inconsistent hw crspace reads: sz %u i %u addr %#lx",
	    sz, i, (unsigned long)addr));

	mdev->dump_size = mlx5_fwdump_getsize(mdev->dump_rege);
	mdev->dump_data = malloc(mdev->dump_size * sizeof(uint32_t),
	    M_MLX5_DUMP, M_WAITOK | M_ZERO);
	mdev->dump_valid = false;
	mdev->dump_copyout = false;

unlock_vsc:
	mlx5_vsc_unlock(mdev);
}