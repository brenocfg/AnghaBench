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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_3__ {int /*<<< orphan*/  command; } ;
struct TYPE_4__ {void* block_size; void* esoc; void* max_burst_len; TYPE_1__ hdr; } ;
typedef  TYPE_2__ sli4_cmd_config_auto_xfer_rdy_hp_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_CONFIG_AUTO_XFER_RDY_HP ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_config_auto_xfer_rdy_hp(sli4_t *sli4, void *buf, size_t size, uint32_t max_burst_len,
                                                uint32_t esoc, uint32_t block_size )
{
        sli4_cmd_config_auto_xfer_rdy_hp_t      *req = buf;

        if (!sli4 || !buf) {
                return 0;
        }

        ocs_memset(buf, 0, size);

        req->hdr.command = SLI4_MBOX_COMMAND_CONFIG_AUTO_XFER_RDY_HP;
        req->max_burst_len = max_burst_len;
        req->esoc = esoc;
        req->block_size = block_size;
        return sizeof(sli4_cmd_config_auto_xfer_rdy_hp_t);
}