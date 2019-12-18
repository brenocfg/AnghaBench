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
struct omap_sham_dev {int err; int /*<<< orphan*/  flags; int /*<<< orphan*/  req; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_BUSY ; 
 int /*<<< orphan*/  FLAGS_CPU ; 
 int /*<<< orphan*/  FLAGS_DMA_ACTIVE ; 
 int /*<<< orphan*/  FLAGS_DMA_READY ; 
 int /*<<< orphan*/  FLAGS_OUTPUT_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  omap_sham_finish_req (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_sham_handle_queue (struct omap_sham_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_sham_update_dma_stop (struct omap_sham_dev*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap_sham_done_task(unsigned long data)
{
	struct omap_sham_dev *dd = (struct omap_sham_dev *)data;
	int err = 0;

	if (!test_bit(FLAGS_BUSY, &dd->flags)) {
		omap_sham_handle_queue(dd, NULL);
		return;
	}

	if (test_bit(FLAGS_CPU, &dd->flags)) {
		if (test_and_clear_bit(FLAGS_OUTPUT_READY, &dd->flags))
			goto finish;
	} else if (test_bit(FLAGS_DMA_READY, &dd->flags)) {
		if (test_and_clear_bit(FLAGS_DMA_ACTIVE, &dd->flags)) {
			omap_sham_update_dma_stop(dd);
			if (dd->err) {
				err = dd->err;
				goto finish;
			}
		}
		if (test_and_clear_bit(FLAGS_OUTPUT_READY, &dd->flags)) {
			/* hash or semi-hash ready */
			clear_bit(FLAGS_DMA_READY, &dd->flags);
			goto finish;
		}
	}

	return;

finish:
	dev_dbg(dd->dev, "update done: err: %d\n", err);
	/* finish curent request */
	omap_sham_finish_req(dd->req, err);

	/* If we are not busy, process next req */
	if (!test_bit(FLAGS_BUSY, &dd->flags))
		omap_sham_handle_queue(dd, NULL);
}