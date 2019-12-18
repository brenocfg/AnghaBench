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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  msg; scalar_t__ completed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int OPAL_BUSY ; 
 int /*<<< orphan*/  OPAL_CHECK_ASYNC_COMPLETION ; 
 int OPAL_SUCCESS ; 
 int /*<<< orphan*/  atomic_thread_fence_acq () ; 
 TYPE_1__* completions ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vtophys (void*) ; 

int
opal_wait_completion(void *buf, uint64_t size, int token)
{
	int err;

	do {
		err = opal_call(OPAL_CHECK_ASYNC_COMPLETION,
		    vtophys(buf), size, token);
		if (err == OPAL_BUSY) {
			if (completions[token].completed) {
				atomic_thread_fence_acq();
				memcpy(buf, &completions[token].msg, size);
				return (OPAL_SUCCESS);
			}
		}
		DELAY(100);
	} while (err == OPAL_BUSY);

	return (err);
}