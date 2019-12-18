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
struct TYPE_3__ {size_t cidx; size_t entry_count; int /*<<< orphan*/  cbuf_psem; int /*<<< orphan*/  cbuf_clock; void** array; int /*<<< orphan*/  cbuf_csem; } ;
typedef  TYPE_1__ ocs_cbuf_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ ocs_sem_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_sem_v (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void*
ocs_cbuf_get(ocs_cbuf_t *cbuf, int32_t timeout_usec)
{
	void *ret = NULL;

	if (likely(ocs_sem_p(&cbuf->cbuf_csem, timeout_usec) == 0)) {
		ocs_lock(&cbuf->cbuf_clock);
			ret = cbuf->array[cbuf->cidx];
			if (unlikely(++cbuf->cidx >= cbuf->entry_count)) {
				cbuf->cidx = 0;
			}
		ocs_unlock(&cbuf->cbuf_clock);
		ocs_sem_v(&cbuf->cbuf_psem);
	}
	return ret;
}