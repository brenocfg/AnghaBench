#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_xrcd {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  xrcdn; int /*<<< orphan*/  pd; int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_destroy_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_xrcd*) ; 
 int /*<<< orphan*/  mlx4_xrcd_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mxrcd (struct ib_xrcd*) ; 

__attribute__((used)) static int mlx4_ib_dealloc_xrcd(struct ib_xrcd *xrcd)
{
	ib_destroy_cq(to_mxrcd(xrcd)->cq);
	ib_dealloc_pd(to_mxrcd(xrcd)->pd);
	mlx4_xrcd_free(to_mdev(xrcd->device)->dev, to_mxrcd(xrcd)->xrcdn);
	kfree(xrcd);

	return 0;
}