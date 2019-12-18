#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_7__ {TYPE_2__* domain; } ;
typedef  TYPE_3__ ocs_t ;
struct TYPE_6__ {TYPE_1__* sport; scalar_t__ attached; } ;
struct TYPE_5__ {int /*<<< orphan*/  fc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RD ; 
 int /*<<< orphan*/  ocs_mgmt_emit_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static void
get_fcid(ocs_t *ocs, char *name, ocs_textbuf_t *textbuf)
{

	if (ocs->domain && ocs->domain->attached) {
		ocs_mgmt_emit_int(textbuf, MGMT_MODE_RD, "fc_id", "0x%06x", 
						ocs->domain->sport->fc_id);
	} else {
		ocs_mgmt_emit_int(textbuf, MGMT_MODE_RD, "fc_id", "UNKNOWN"); 
	}

}