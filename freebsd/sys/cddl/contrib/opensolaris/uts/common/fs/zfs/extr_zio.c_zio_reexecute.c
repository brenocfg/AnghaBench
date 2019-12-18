#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ io_child_type; scalar_t__ io_orig_stage; int io_flags; int io_orig_flags; scalar_t__ io_stage; int /*<<< orphan*/  io_queued_timestamp; int /*<<< orphan*/  io_lock; int /*<<< orphan*/ ** io_children; int /*<<< orphan*/  io_bp; scalar_t__* io_child_error; scalar_t__* io_state; scalar_t__ io_error; scalar_t__ io_pipeline_trace; scalar_t__ io_reexecute; int /*<<< orphan*/  io_orig_pipeline; int /*<<< orphan*/  io_pipeline; int /*<<< orphan*/ * io_gang_tree; int /*<<< orphan*/ * io_gang_leader; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  zio_link_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BP_ZERO (int /*<<< orphan*/ ) ; 
 scalar_t__ IO_IS_ALLOCATING (TYPE_1__*) ; 
 scalar_t__ ZIO_CHILD_LOGICAL ; 
 int ZIO_CHILD_TYPES ; 
 int ZIO_FLAG_GODFATHER ; 
 int ZIO_FLAG_REEXECUTED ; 
 scalar_t__ ZIO_STAGE_OPEN ; 
 int ZIO_WAIT_TYPES ; 
 int /*<<< orphan*/  gethrtime () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_execute (TYPE_1__*) ; 
 TYPE_1__* zio_walk_children (TYPE_1__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
zio_reexecute(zio_t *pio)
{
	zio_t *cio, *cio_next;

	ASSERT(pio->io_child_type == ZIO_CHILD_LOGICAL);
	ASSERT(pio->io_orig_stage == ZIO_STAGE_OPEN);
	ASSERT(pio->io_gang_leader == NULL);
	ASSERT(pio->io_gang_tree == NULL);

	pio->io_flags = pio->io_orig_flags;
	pio->io_stage = pio->io_orig_stage;
	pio->io_pipeline = pio->io_orig_pipeline;
	pio->io_reexecute = 0;
	pio->io_flags |= ZIO_FLAG_REEXECUTED;
	pio->io_pipeline_trace = 0;
	pio->io_error = 0;
	for (int w = 0; w < ZIO_WAIT_TYPES; w++)
		pio->io_state[w] = 0;
	for (int c = 0; c < ZIO_CHILD_TYPES; c++)
		pio->io_child_error[c] = 0;

	if (IO_IS_ALLOCATING(pio))
		BP_ZERO(pio->io_bp);

	/*
	 * As we reexecute pio's children, new children could be created.
	 * New children go to the head of pio's io_child_list, however,
	 * so we will (correctly) not reexecute them.  The key is that
	 * the remainder of pio's io_child_list, from 'cio_next' onward,
	 * cannot be affected by any side effects of reexecuting 'cio'.
	 */
	zio_link_t *zl = NULL;
	mutex_enter(&pio->io_lock);
	for (cio = zio_walk_children(pio, &zl); cio != NULL; cio = cio_next) {
		cio_next = zio_walk_children(pio, &zl);
		for (int w = 0; w < ZIO_WAIT_TYPES; w++)
			pio->io_children[cio->io_child_type][w]++;
		mutex_exit(&pio->io_lock);
		zio_reexecute(cio);
		mutex_enter(&pio->io_lock);
	}
	mutex_exit(&pio->io_lock);

	/*
	 * Now that all children have been reexecuted, execute the parent.
	 * We don't reexecute "The Godfather" I/O here as it's the
	 * responsibility of the caller to wait on it.
	 */
	if (!(pio->io_flags & ZIO_FLAG_GODFATHER)) {
		pio->io_queued_timestamp = gethrtime();
		zio_execute(pio);
	}
}