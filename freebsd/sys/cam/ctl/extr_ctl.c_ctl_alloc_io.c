#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* pool; } ;
union ctl_io {TYPE_1__ io_hdr; } ;
struct ctl_io_pool {TYPE_3__* ctl_softc; int /*<<< orphan*/  zone; } ;
struct TYPE_5__ {int /*<<< orphan*/  blocked_queue; } ;
struct TYPE_6__ {TYPE_2__ io_hdr; } ;
typedef  TYPE_3__* CTL_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 union ctl_io* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

union ctl_io *
ctl_alloc_io(void *pool_ref)
{
	struct ctl_io_pool *pool = (struct ctl_io_pool *)pool_ref;
	union ctl_io *io;

	io = uma_zalloc(pool->zone, M_WAITOK);
	if (io != NULL) {
		io->io_hdr.pool = pool_ref;
		CTL_SOFTC(io) = pool->ctl_softc;
		TAILQ_INIT(&io->io_hdr.blocked_queue);
	}
	return (io);
}