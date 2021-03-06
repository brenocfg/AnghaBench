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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_3__ {int /*<<< orphan*/  command; } ;
struct TYPE_4__ {int /*<<< orphan*/  fcfi; TYPE_1__ hdr; } ;
typedef  TYPE_2__ sli4_cmd_unreg_fcfi_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_UNREG_FCFI ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_unreg_fcfi(sli4_t *sli4, void *buf, size_t size, uint16_t indicator)
{
	sli4_cmd_unreg_fcfi_t	*unreg_fcfi = buf;

	if (!sli4 || !buf) {
		return 0;
	}

	ocs_memset(buf, 0, size);

	unreg_fcfi->hdr.command = SLI4_MBOX_COMMAND_UNREG_FCFI;

	unreg_fcfi->fcfi = indicator;

	return sizeof(sli4_cmd_unreg_fcfi_t);
}