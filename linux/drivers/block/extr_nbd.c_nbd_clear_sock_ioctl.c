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
struct nbd_device {TYPE_1__* config; } ;
struct block_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBD_RT_HAS_CONFIG_REF ; 
 int /*<<< orphan*/  __invalidate_device (struct block_device*,int) ; 
 int /*<<< orphan*/  nbd_bdev_reset (struct block_device*) ; 
 int /*<<< orphan*/  nbd_config_put (struct nbd_device*) ; 
 int /*<<< orphan*/  sock_shutdown (struct nbd_device*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nbd_clear_sock_ioctl(struct nbd_device *nbd,
				 struct block_device *bdev)
{
	sock_shutdown(nbd);
	__invalidate_device(bdev, true);
	nbd_bdev_reset(bdev);
	if (test_and_clear_bit(NBD_RT_HAS_CONFIG_REF,
			       &nbd->config->runtime_flags))
		nbd_config_put(nbd);
}