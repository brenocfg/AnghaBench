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
struct img_hash_dev {int err; int flags; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int DRIVER_FLAGS_BUSY ; 
 int DRIVER_FLAGS_CPU ; 
 int DRIVER_FLAGS_DMA_ACTIVE ; 
 int DRIVER_FLAGS_DMA_READY ; 
 int DRIVER_FLAGS_OUTPUT_READY ; 
 int EINVAL ; 
 int /*<<< orphan*/  img_hash_finish_req (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  img_hash_handle_queue (struct img_hash_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  img_hash_write_via_dma_stop (struct img_hash_dev*) ; 

__attribute__((used)) static void img_hash_done_task(unsigned long data)
{
	struct img_hash_dev *hdev = (struct img_hash_dev *)data;
	int err = 0;

	if (hdev->err == -EINVAL) {
		err = hdev->err;
		goto finish;
	}

	if (!(DRIVER_FLAGS_BUSY & hdev->flags)) {
		img_hash_handle_queue(hdev, NULL);
		return;
	}

	if (DRIVER_FLAGS_CPU & hdev->flags) {
		if (DRIVER_FLAGS_OUTPUT_READY & hdev->flags) {
			hdev->flags &= ~DRIVER_FLAGS_OUTPUT_READY;
			goto finish;
		}
	} else if (DRIVER_FLAGS_DMA_READY & hdev->flags) {
		if (DRIVER_FLAGS_DMA_ACTIVE & hdev->flags) {
			hdev->flags &= ~DRIVER_FLAGS_DMA_ACTIVE;
			img_hash_write_via_dma_stop(hdev);
			if (hdev->err) {
				err = hdev->err;
				goto finish;
			}
		}
		if (DRIVER_FLAGS_OUTPUT_READY & hdev->flags) {
			hdev->flags &= ~(DRIVER_FLAGS_DMA_READY |
					DRIVER_FLAGS_OUTPUT_READY);
			goto finish;
		}
	}
	return;

finish:
	img_hash_finish_req(hdev->req, err);
}