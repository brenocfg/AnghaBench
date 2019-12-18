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
struct rbd_img_request {int work_result; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_img_handle_request_work ; 
 int /*<<< orphan*/  rbd_wq ; 

__attribute__((used)) static void rbd_img_schedule(struct rbd_img_request *img_req, int result)
{
	INIT_WORK(&img_req->work, rbd_img_handle_request_work);
	img_req->work_result = result;
	queue_work(rbd_wq, &img_req->work);
}