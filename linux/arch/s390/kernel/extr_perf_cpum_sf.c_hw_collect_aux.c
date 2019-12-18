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
struct perf_output_handle {int size; int head; } ;
struct cpu_hw_sf {struct perf_output_handle handle; int /*<<< orphan*/  event; } ;
struct TYPE_2__ {unsigned long num_sdb; } ;
struct aux_buffer {int head; unsigned long alert_mark; int /*<<< orphan*/  empty_mark; TYPE_1__ sfb; } ;

/* Variables and functions */
 int AUX_SDB_NUM_ALERT (struct aux_buffer*) ; 
 int PAGE_SHIFT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ aux_reset_buffer (struct aux_buffer*,unsigned long,unsigned long long*) ; 
 int /*<<< orphan*/  debug_sprintf_event (int /*<<< orphan*/ ,int,char*,...) ; 
 struct aux_buffer* perf_aux_output_begin (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_aux_output_end (struct perf_output_handle*,unsigned long) ; 
 struct aux_buffer* perf_get_aux (struct perf_output_handle*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long) ; 
 int /*<<< orphan*/  sfdbg ; 

__attribute__((used)) static void hw_collect_aux(struct cpu_hw_sf *cpuhw)
{
	struct aux_buffer *aux;
	int done = 0;
	unsigned long range = 0, size;
	unsigned long long overflow = 0;
	struct perf_output_handle *handle = &cpuhw->handle;
	unsigned long num_sdb;

	aux = perf_get_aux(handle);
	if (WARN_ON_ONCE(!aux))
		return;

	/* Inform user space new data arrived */
	size = AUX_SDB_NUM_ALERT(aux) << PAGE_SHIFT;
	perf_aux_output_end(handle, size);
	num_sdb = aux->sfb.num_sdb;

	while (!done) {
		/* Get an output handle */
		aux = perf_aux_output_begin(handle, cpuhw->event);
		if (handle->size == 0) {
			pr_err("The AUX buffer with %lu pages for the "
			       "diagnostic-sampling mode is full\n",
				num_sdb);
			debug_sprintf_event(sfdbg, 1, "AUX buffer used up\n");
			break;
		}
		if (WARN_ON_ONCE(!aux))
			return;

		/* Update head and alert_mark to new position */
		aux->head = handle->head >> PAGE_SHIFT;
		range = (handle->size + 1) >> PAGE_SHIFT;
		if (range == 1)
			aux->alert_mark = aux->head;
		else
			aux->alert_mark = aux->head + range/2 - 1;

		if (aux_reset_buffer(aux, range, &overflow)) {
			if (!overflow) {
				done = 1;
				break;
			}
			size = range << PAGE_SHIFT;
			perf_aux_output_end(&cpuhw->handle, size);
			pr_err("Sample data caused the AUX buffer with %lu "
			       "pages to overflow\n", num_sdb);
			debug_sprintf_event(sfdbg, 1, "head %lx range %lx "
					    "overflow %llx\n",
					    aux->head, range, overflow);
		} else {
			size = AUX_SDB_NUM_ALERT(aux) << PAGE_SHIFT;
			perf_aux_output_end(&cpuhw->handle, size);
			debug_sprintf_event(sfdbg, 6, "head %lx alert %lx "
					    "already full, try another\n",
					    aux->head, aux->alert_mark);
		}
	}

	if (done)
		debug_sprintf_event(sfdbg, 6, "aux_reset_buffer: "
				    "[%lx -> %lx -> %lx] (%lx, %lx)\n",
				    aux->head, aux->alert_mark, aux->empty_mark,
				    AUX_SDB_NUM_ALERT(aux), range);
}