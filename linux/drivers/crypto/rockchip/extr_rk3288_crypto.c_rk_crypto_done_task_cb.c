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
struct rk_crypto_info {scalar_t__ err; int /*<<< orphan*/  async_req; int /*<<< orphan*/  (* complete ) (int /*<<< orphan*/ ,scalar_t__) ;scalar_t__ (* update ) (struct rk_crypto_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub2 (struct rk_crypto_info*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rk_crypto_done_task_cb(unsigned long data)
{
	struct rk_crypto_info *dev = (struct rk_crypto_info *)data;

	if (dev->err) {
		dev->complete(dev->async_req, dev->err);
		return;
	}

	dev->err = dev->update(dev);
	if (dev->err)
		dev->complete(dev->async_req, dev->err);
}