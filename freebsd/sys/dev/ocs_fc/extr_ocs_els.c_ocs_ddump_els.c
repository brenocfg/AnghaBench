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
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_4__ {int /*<<< orphan*/  els_active; int /*<<< orphan*/  els_pend; int /*<<< orphan*/  els_evtdepth; int /*<<< orphan*/  els_req_free; } ;
typedef  TYPE_1__ ocs_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_ddump_endsection (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ocs_ddump_io (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_ddump_section (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ocs_ddump_value (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

void
ocs_ddump_els(ocs_textbuf_t *textbuf, ocs_io_t *els)
{
	ocs_ddump_section(textbuf, "els", -1);
	ocs_ddump_value(textbuf, "req_free", "%d", els->els_req_free);
	ocs_ddump_value(textbuf, "evtdepth", "%d", els->els_evtdepth);
	ocs_ddump_value(textbuf, "pend", "%d", els->els_pend);
	ocs_ddump_value(textbuf, "active", "%d", els->els_active);
	ocs_ddump_io(textbuf, els);
	ocs_ddump_endsection(textbuf, "els", -1);
}