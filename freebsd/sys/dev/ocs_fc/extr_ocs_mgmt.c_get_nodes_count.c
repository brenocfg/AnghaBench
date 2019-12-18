#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nodes_count; } ;
typedef  TYPE_1__ ocs_xport_t ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_5__ {TYPE_1__* xport; } ;
typedef  TYPE_2__ ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RD ; 
 int /*<<< orphan*/  ocs_mgmt_emit_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_nodes_count(ocs_t *ocs, char *name, ocs_textbuf_t *textbuf)
{
	ocs_xport_t *xport = ocs->xport;

	ocs_mgmt_emit_int(textbuf, MGMT_MODE_RD, "nodes_count", "%d", xport->nodes_count);
}