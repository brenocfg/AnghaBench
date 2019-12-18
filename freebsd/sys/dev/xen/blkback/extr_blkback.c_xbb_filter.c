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
struct xbb_softc {int /*<<< orphan*/  io_task; int /*<<< orphan*/  io_taskqueue; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xbb_filter(void *arg)
{
	struct xbb_softc *xbb;

	/* Defer to taskqueue thread. */
	xbb = (struct xbb_softc *)arg;
	taskqueue_enqueue(xbb->io_taskqueue, &xbb->io_task); 

	return (FILTER_HANDLED);
}