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
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {int /*<<< orphan*/  len; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/ * rx_buf; } ;
struct moxtet {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  count; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int) ; 
 int /*<<< orphan*/  to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int moxtet_spi_read(struct moxtet *moxtet, u8 *buf)
{
	struct spi_transfer xfer = {
		.rx_buf = buf,
		.tx_buf = moxtet->tx,
		.len = moxtet->count + 1
	};
	int ret;

	mutex_lock(&moxtet->lock);

	ret = spi_sync_transfer(to_spi_device(moxtet->dev), &xfer, 1);

	mutex_unlock(&moxtet->lock);

	return ret;
}