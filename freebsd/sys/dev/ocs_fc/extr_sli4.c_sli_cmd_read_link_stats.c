#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_3__ {int /*<<< orphan*/  command; } ;
struct TYPE_4__ {void* clof; void* clrc; void* rec; TYPE_1__ hdr; } ;
typedef  TYPE_2__ sli4_cmd_read_link_stats_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_READ_LNK_STAT ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_read_link_stats(sli4_t *sli4, void *buf, size_t size,
			uint8_t req_ext_counters,
			uint8_t clear_overflow_flags,
			uint8_t clear_all_counters)
{
	sli4_cmd_read_link_stats_t	*cmd = buf;

	ocs_memset(buf, 0, size);

	cmd->hdr.command = SLI4_MBOX_COMMAND_READ_LNK_STAT;
	cmd->rec = req_ext_counters;
	cmd->clrc = clear_all_counters;
	cmd->clof = clear_overflow_flags;
	return sizeof(sli4_cmd_read_link_stats_t);
}