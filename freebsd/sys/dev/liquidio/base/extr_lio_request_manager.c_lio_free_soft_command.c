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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  alloc_buf_count; int /*<<< orphan*/  head; } ;
struct octeon_device {TYPE_1__ sc_buf_pool; } ;
struct lio_soft_command {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
lio_free_soft_command(struct octeon_device *oct,
		      struct lio_soft_command *sc)
{

	mtx_lock(&oct->sc_buf_pool.lock);

	STAILQ_INSERT_TAIL(&oct->sc_buf_pool.head, &sc->node, entries);

	atomic_subtract_int(&oct->sc_buf_pool.alloc_buf_count, 1);

	mtx_unlock(&oct->sc_buf_pool.lock);
}