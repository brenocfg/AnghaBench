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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_3__ {int /*<<< orphan*/  command; } ;
struct TYPE_4__ {int /*<<< orphan*/  preferred_d_id; int /*<<< orphan*/  hard_alpa; int /*<<< orphan*/  wwnn; int /*<<< orphan*/  wwpn; TYPE_1__ hdr; } ;
typedef  TYPE_2__ sli4_cmd_write_nvparms_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_WRITE_NVPARMS ; 
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_write_nvparms(sli4_t *sli4, void *buf, size_t size, uint8_t *wwpn, uint8_t *wwnn, uint8_t hard_alpa,
		uint32_t preferred_d_id)
{
	sli4_cmd_write_nvparms_t	*write_nvparms = buf;

	ocs_memset(buf, 0, size);

	write_nvparms->hdr.command = SLI4_MBOX_COMMAND_WRITE_NVPARMS;
	ocs_memcpy(write_nvparms->wwpn, wwpn, 8);
	ocs_memcpy(write_nvparms->wwnn, wwnn, 8);
	write_nvparms->hard_alpa = hard_alpa;
	write_nvparms->preferred_d_id = preferred_d_id;

	return sizeof(sli4_cmd_write_nvparms_t);
}