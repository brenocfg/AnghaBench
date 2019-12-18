#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; int /*<<< orphan*/  device; } ;
struct mlx4_ib_fmr {TYPE_1__ ibfmr; int /*<<< orphan*/  mfmr; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_fmr {int dummy; } ;

/* Variables and functions */
 int mlx4_map_phys_fmr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_fmr* to_mfmr (struct ib_fmr*) ; 

int mlx4_ib_map_phys_fmr(struct ib_fmr *ibfmr, u64 *page_list,
		      int npages, u64 iova)
{
	struct mlx4_ib_fmr *ifmr = to_mfmr(ibfmr);
	struct mlx4_ib_dev *dev = to_mdev(ifmr->ibfmr.device);

	return mlx4_map_phys_fmr(dev->dev, &ifmr->mfmr, page_list, npages, iova,
				 &ifmr->ibfmr.lkey, &ifmr->ibfmr.rkey);
}