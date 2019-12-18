#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int entry_count; int /*<<< orphan*/  os; int /*<<< orphan*/  cbuf_plock; int /*<<< orphan*/  cbuf_clock; struct TYPE_4__* array; } ;
typedef  TYPE_1__ ocs_cbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ocs_lock_free (int /*<<< orphan*/ *) ; 

void
ocs_cbuf_free(ocs_cbuf_t *cbuf)
{
	if (cbuf != NULL) {
		if (cbuf->array != NULL) {
			ocs_free(cbuf->os, cbuf->array, sizeof(*cbuf->array) * cbuf->entry_count);
		}
		ocs_lock_free(&cbuf->cbuf_clock);
		ocs_lock_free(&cbuf->cbuf_plock);
		ocs_free(cbuf->os, cbuf, sizeof(*cbuf));
	}
}