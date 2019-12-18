#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ocs_os_handle_t ;
struct TYPE_6__ {int entry_count; int /*<<< orphan*/ * array; int /*<<< orphan*/  cbuf_psem; int /*<<< orphan*/  cbuf_csem; int /*<<< orphan*/  cbuf_plock; int /*<<< orphan*/  cbuf_clock; scalar_t__ cidx; scalar_t__ pidx; int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_cbuf_t ;

/* Variables and functions */
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int /*<<< orphan*/  ocs_cbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 void* ocs_malloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ocs_sem_init (int /*<<< orphan*/ *,int,char*,TYPE_1__*) ; 

ocs_cbuf_t*
ocs_cbuf_alloc(ocs_os_handle_t os, uint32_t entry_count)
{
	ocs_cbuf_t *cbuf;

	cbuf = ocs_malloc(os, sizeof(*cbuf), OCS_M_NOWAIT | OCS_M_ZERO);
	if (cbuf == NULL) {
		return NULL;
	}

	cbuf->os = os;
	cbuf->entry_count = entry_count;
	cbuf->pidx = 0;
	cbuf->cidx = 0;

	ocs_lock_init(NULL, &cbuf->cbuf_clock, "cbuf_c:%p", cbuf);
	ocs_lock_init(NULL, &cbuf->cbuf_plock, "cbuf_p:%p", cbuf);
	ocs_sem_init(&cbuf->cbuf_csem, 0, "cbuf:%p", cbuf);
	ocs_sem_init(&cbuf->cbuf_psem, cbuf->entry_count, "cbuf:%p", cbuf);

	cbuf->array = ocs_malloc(os, entry_count * sizeof(*cbuf->array), OCS_M_NOWAIT | OCS_M_ZERO);
	if (cbuf->array == NULL) {
		ocs_cbuf_free(cbuf);
		return NULL;
	}

	return cbuf;
}