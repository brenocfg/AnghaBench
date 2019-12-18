#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pcd_unit {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bio; TYPE_1__* rq_disk; } ;
struct TYPE_5__ {struct pcd_unit* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_cur_sectors (TYPE_2__*) ; 
 int /*<<< orphan*/  blk_rq_pos (TYPE_2__*) ; 
 int /*<<< orphan*/  do_pcd_read ; 
 int /*<<< orphan*/  nice ; 
 int /*<<< orphan*/  pcd_buf ; 
 int pcd_bufblk ; 
 int pcd_busy ; 
 int /*<<< orphan*/  pcd_count ; 
 struct pcd_unit* pcd_current ; 
 TYPE_2__* pcd_req ; 
 int /*<<< orphan*/  pcd_sector ; 
 int /*<<< orphan*/  ps_set_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_next_request () ; 

__attribute__((used)) static void pcd_request(void)
{
	struct pcd_unit *cd;

	if (pcd_busy)
		return;

	if (!pcd_req && !set_next_request())
		return;

	cd = pcd_req->rq_disk->private_data;
	if (cd != pcd_current)
		pcd_bufblk = -1;
	pcd_current = cd;
	pcd_sector = blk_rq_pos(pcd_req);
	pcd_count = blk_rq_cur_sectors(pcd_req);
	pcd_buf = bio_data(pcd_req->bio);
	pcd_busy = 1;
	ps_set_intr(do_pcd_read, NULL, 0, nice);
}