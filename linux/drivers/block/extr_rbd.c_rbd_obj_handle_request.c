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
struct rbd_obj_request {int /*<<< orphan*/  img_request; } ;

/* Variables and functions */
 scalar_t__ __rbd_obj_handle_request (struct rbd_obj_request*,int*) ; 
 int /*<<< orphan*/  rbd_img_handle_request (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rbd_obj_handle_request(struct rbd_obj_request *obj_req, int result)
{
	if (__rbd_obj_handle_request(obj_req, &result))
		rbd_img_handle_request(obj_req->img_request, result);
}