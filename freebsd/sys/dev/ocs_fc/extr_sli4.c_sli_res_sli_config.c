#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* embed; } ;
struct TYPE_5__ {scalar_t__ command; int status; } ;
struct TYPE_6__ {TYPE_1__ payload; scalar_t__ emb; TYPE_2__ hdr; } ;
typedef  TYPE_3__ sli4_cmd_sli_config_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ SLI4_MBOX_COMMAND_SLI_CONFIG ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,void*,int) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int32_t
sli_res_sli_config(void *buf)
{
	sli4_cmd_sli_config_t	*sli_config = buf;

	if (!buf || (SLI4_MBOX_COMMAND_SLI_CONFIG != sli_config->hdr.command)) {
		ocs_log_err(NULL, "bad parameter buf=%p cmd=%#x\n", buf,
				buf ? sli_config->hdr.command : -1);
		return -1;
	}

	if (sli_config->hdr.status) {
		return sli_config->hdr.status;
	}

	if (sli_config->emb) {
		return sli_config->payload.embed[4];
	} else {
		ocs_log_test(NULL, "external buffers not supported\n");
		return -1;
	}
}