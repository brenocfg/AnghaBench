#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_6__ {char* indicator; char* state; char* reqtag; char* abort_reqtag; char* abort_in_progress; char* type; char* xbusy; char* def_sgl_count; char* n_sge; int /*<<< orphan*/ * ovfl_io; int /*<<< orphan*/ * ovfl_sgl; int /*<<< orphan*/  wqe_link; TYPE_1__* wq; int /*<<< orphan*/  ref; } ;
typedef  TYPE_2__ ocs_hw_io_t ;
struct TYPE_5__ {int instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_assert (TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_ddump_endsection (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ocs_ddump_section (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ocs_ddump_value (int /*<<< orphan*/ *,char*,char*,...) ; 
 char* ocs_list_on_list (int /*<<< orphan*/ *) ; 
 char* ocs_ref_read_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_ddump_hw_io(ocs_textbuf_t *textbuf, ocs_hw_io_t *io)
{
	ocs_assert(io);

	ocs_ddump_section(textbuf, "hw_io", io->indicator);

	ocs_ddump_value(textbuf, "state", "%d", io->state);
	ocs_ddump_value(textbuf, "xri", "0x%x", io->indicator);
	ocs_ddump_value(textbuf, "tag", "0x%x", io->reqtag);
	ocs_ddump_value(textbuf, "abort_reqtag", "0x%x", io->abort_reqtag);
	ocs_ddump_value(textbuf, "ref_count", "%d", ocs_ref_read_count(&io->ref));

	/* just to make it obvious, display abort bit from tag */
	ocs_ddump_value(textbuf, "abort", "0x%x", io->abort_in_progress);
	ocs_ddump_value(textbuf, "wq_index", "%d", (io->wq == NULL ? 0xffff : io->wq->instance));
	ocs_ddump_value(textbuf, "type", "%d", io->type);
	ocs_ddump_value(textbuf, "xbusy", "%d", io->xbusy);
	ocs_ddump_value(textbuf, "active_wqe_link", "%d", ocs_list_on_list(&io->wqe_link));
	ocs_ddump_value(textbuf, "def_sgl_count", "%d", io->def_sgl_count);
	ocs_ddump_value(textbuf, "n_sge", "%d", io->n_sge);
	ocs_ddump_value(textbuf, "has_ovfl_sgl", "%s", (io->ovfl_sgl != NULL ? "TRUE" : "FALSE"));
	ocs_ddump_value(textbuf, "has_ovfl_io", "%s", (io->ovfl_io != NULL ? "TRUE" : "FALSE"));

	ocs_ddump_endsection(textbuf, "hw_io", io->indicator);
}