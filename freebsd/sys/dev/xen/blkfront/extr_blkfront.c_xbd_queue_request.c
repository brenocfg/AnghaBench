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
struct xbd_softc {int /*<<< orphan*/  xbd_io_dmat; } ;
struct xbd_command {int /*<<< orphan*/  cm_datalen; int /*<<< orphan*/  cm_data; int /*<<< orphan*/  cm_map; int /*<<< orphan*/ * cm_bp; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  XBDCF_ASYNC_MAPPING ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xbd_command*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xbd_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_cm_freeze (struct xbd_softc*,struct xbd_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_queue_cb ; 

__attribute__((used)) static int
xbd_queue_request(struct xbd_softc *sc, struct xbd_command *cm)
{
	int error;

	if (cm->cm_bp != NULL)
		error = bus_dmamap_load_bio(sc->xbd_io_dmat, cm->cm_map,
		    cm->cm_bp, xbd_queue_cb, cm, 0);
	else
		error = bus_dmamap_load(sc->xbd_io_dmat, cm->cm_map,
		    cm->cm_data, cm->cm_datalen, xbd_queue_cb, cm, 0);
	if (error == EINPROGRESS) {
		/*
		 * Maintain queuing order by freezing the queue.  The next
		 * command may not require as many resources as the command
		 * we just attempted to map, so we can't rely on bus dma
		 * blocking for it too.
		 */
		xbd_cm_freeze(sc, cm, XBDCF_ASYNC_MAPPING);
		return (0);
	}

	return (error);
}