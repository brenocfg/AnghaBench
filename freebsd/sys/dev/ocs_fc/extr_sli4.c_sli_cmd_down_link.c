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
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;
typedef  TYPE_1__ sli4_mbox_command_header_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_DOWN_LINK ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_down_link(sli4_t *sli4, void *buf, size_t size)
{
	sli4_mbox_command_header_t	*hdr = buf;

	ocs_memset(buf, 0, size);

	hdr->command = SLI4_MBOX_COMMAND_DOWN_LINK;

	/* Port interprets zero in a field as "use default value" */

	return sizeof(sli4_mbox_command_header_t);
}