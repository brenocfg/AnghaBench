#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bulk_transfer_mutex; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lmutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause_bulks_count ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
pause_bulks(VCHIQ_STATE_T *state)
{
	if (unlikely(atomic_inc_return(&pause_bulks_count) != 1)) {
		WARN_ON_ONCE(1);
		atomic_set(&pause_bulks_count, 1);
		return;
	}

	/* Block bulk transfers from all services */
	lmutex_lock(&state->bulk_transfer_mutex);
}