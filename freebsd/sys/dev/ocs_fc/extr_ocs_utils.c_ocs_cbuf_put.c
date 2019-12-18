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
struct TYPE_3__ {size_t pidx; size_t entry_count; int /*<<< orphan*/  cbuf_csem; int /*<<< orphan*/  cbuf_plock; void** array; int /*<<< orphan*/  cbuf_psem; } ;
typedef  TYPE_1__ ocs_cbuf_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ ocs_sem_p (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_sem_v (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int32_t
ocs_cbuf_put(ocs_cbuf_t *cbuf, void *elem)
{
	int32_t rc = 0;

	if (likely(ocs_sem_p(&cbuf->cbuf_psem, -1) == 0)) {
		ocs_lock(&cbuf->cbuf_plock);
			cbuf->array[cbuf->pidx] = elem;
			if (unlikely(++cbuf->pidx >= cbuf->entry_count)) {
				cbuf->pidx = 0;
			}
		ocs_unlock(&cbuf->cbuf_plock);
		ocs_sem_v(&cbuf->cbuf_csem);
	} else {
		rc = -1;
	}
	return rc;
}