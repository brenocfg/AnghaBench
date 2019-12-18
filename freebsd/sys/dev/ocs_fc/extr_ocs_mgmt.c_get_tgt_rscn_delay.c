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
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_3__ {scalar_t__ tgt_rscn_delay_msec; } ;
typedef  TYPE_1__ ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RW ; 
 int /*<<< orphan*/  ocs_mgmt_emit_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,unsigned long) ; 

__attribute__((used)) static void
get_tgt_rscn_delay(ocs_t *ocs, char *name, ocs_textbuf_t *textbuf)
{
	ocs_mgmt_emit_int(textbuf, MGMT_MODE_RW, "tgt_rscn_delay", "%ld", (unsigned long)ocs->tgt_rscn_delay_msec / 1000);
}