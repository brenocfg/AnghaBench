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
struct xbb_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev_name; int /*<<< orphan*/ * dev_type; int /*<<< orphan*/ * dev_mode; int /*<<< orphan*/ * xbb_stats_in; int /*<<< orphan*/ * xbb_stats; int /*<<< orphan*/ * io_taskqueue; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  M_XENSTORE ; 
 struct xbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devstat_remove_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct xbb_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xbb_close_backend (struct xbb_softc*) ; 
 scalar_t__ xbb_shutdown (struct xbb_softc*) ; 

__attribute__((used)) static int
xbb_detach(device_t dev)
{
        struct xbb_softc *xbb;

	DPRINTF("\n");

        xbb = device_get_softc(dev);
	mtx_lock(&xbb->lock);
	while (xbb_shutdown(xbb) == EAGAIN) {
		msleep(xbb, &xbb->lock, /*wakeup prio unchanged*/0,
		       "xbb_shutdown", 0);
	}
	mtx_unlock(&xbb->lock);

	DPRINTF("\n");

	if (xbb->io_taskqueue != NULL)
		taskqueue_free(xbb->io_taskqueue);

	if (xbb->xbb_stats != NULL)
		devstat_remove_entry(xbb->xbb_stats);

	if (xbb->xbb_stats_in != NULL)
		devstat_remove_entry(xbb->xbb_stats_in);

	xbb_close_backend(xbb);

	if (xbb->dev_mode != NULL) {
		free(xbb->dev_mode, M_XENSTORE);
		xbb->dev_mode = NULL;
	}

	if (xbb->dev_type != NULL) {
		free(xbb->dev_type, M_XENSTORE);
		xbb->dev_type = NULL;
	}

	if (xbb->dev_name != NULL) {
		free(xbb->dev_name, M_XENSTORE);
		xbb->dev_name = NULL;
	}

	mtx_destroy(&xbb->lock);
        return (0);
}