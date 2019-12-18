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
typedef  int /*<<< orphan*/  u32 ;
struct qlnxr_dev {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  qpidr; int /*<<< orphan*/ * ha; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLNX_IS_IWARP (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnxr_idr_remove(struct qlnxr_dev *dev, u32 id)
{
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	if (!QLNX_IS_IWARP(dev))
		return;

	mtx_lock(&dev->idr_lock);
	idr_remove(&dev->qpidr, id);
	mtx_unlock(&dev->idr_lock);

	QL_DPRINT12(ha, "exit \n");

	return;
}