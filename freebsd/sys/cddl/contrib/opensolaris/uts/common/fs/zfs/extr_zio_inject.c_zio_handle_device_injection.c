#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ io_offset; int io_flags; scalar_t__ io_type; } ;
typedef  TYPE_3__ zio_t ;
struct TYPE_11__ {int /*<<< orphan*/  vs_aux; } ;
struct TYPE_14__ {scalar_t__ vdev_psize; scalar_t__ vdev_guid; TYPE_1__ vdev_stat; } ;
typedef  TYPE_4__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_12__ {scalar_t__ zi_cmd; scalar_t__ zi_guid; scalar_t__ zi_iotype; int zi_error; scalar_t__ zi_failfast; } ;
struct TYPE_15__ {TYPE_2__ zi_record; } ;
typedef  TYPE_5__ inject_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VDEV_AUX_OPEN_FAILED ; 
 scalar_t__ VDEV_LABEL_END_SIZE ; 
 scalar_t__ VDEV_LABEL_START_SIZE ; 
 scalar_t__ ZINJECT_DEVICE_FAULT ; 
 int ZIO_FLAG_IO_RETRY ; 
 int ZIO_FLAG_TRYHARD ; 
 scalar_t__ ZIO_TYPES ; 
 int /*<<< orphan*/  inject_handlers ; 
 int /*<<< orphan*/  inject_lock ; 
 TYPE_5__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_5__* list_next (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

int
zio_handle_device_injection(vdev_t *vd, zio_t *zio, int error)
{
	inject_handler_t *handler;
	int ret = 0;

	/*
	 * We skip over faults in the labels unless it's during
	 * device open (i.e. zio == NULL).
	 */
	if (zio != NULL) {
		uint64_t offset = zio->io_offset;

		if (offset < VDEV_LABEL_START_SIZE ||
		    offset >= vd->vdev_psize - VDEV_LABEL_END_SIZE)
			return (0);
	}

	rw_enter(&inject_lock, RW_READER);

	for (handler = list_head(&inject_handlers); handler != NULL;
	    handler = list_next(&inject_handlers, handler)) {

		if (handler->zi_record.zi_cmd != ZINJECT_DEVICE_FAULT)
			continue;

		if (vd->vdev_guid == handler->zi_record.zi_guid) {
			if (handler->zi_record.zi_failfast &&
			    (zio == NULL || (zio->io_flags &
			    (ZIO_FLAG_IO_RETRY | ZIO_FLAG_TRYHARD)))) {
				continue;
			}

			/* Handle type specific I/O failures */
			if (zio != NULL &&
			    handler->zi_record.zi_iotype != ZIO_TYPES &&
			    handler->zi_record.zi_iotype != zio->io_type)
				continue;

			if (handler->zi_record.zi_error == error) {
				/*
				 * For a failed open, pretend like the device
				 * has gone away.
				 */
				if (error == ENXIO)
					vd->vdev_stat.vs_aux =
					    VDEV_AUX_OPEN_FAILED;

				/*
				 * Treat these errors as if they had been
				 * retried so that all the appropriate stats
				 * and FMA events are generated.
				 */
				if (!handler->zi_record.zi_failfast &&
				    zio != NULL)
					zio->io_flags |= ZIO_FLAG_IO_RETRY;

				ret = error;
				break;
			}
			if (handler->zi_record.zi_error == ENXIO) {
				ret = SET_ERROR(EIO);
				break;
			}
		}
	}

	rw_exit(&inject_lock);

	return (ret);
}