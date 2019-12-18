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
struct rbd_img_request {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_REQ_LAYERED ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool img_request_layered_test(struct rbd_img_request *img_request)
{
	smp_mb();
	return test_bit(IMG_REQ_LAYERED, &img_request->flags) != 0;
}