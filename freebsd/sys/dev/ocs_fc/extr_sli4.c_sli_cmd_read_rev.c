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
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_5__ {int /*<<< orphan*/  command; } ;
struct TYPE_6__ {int /*<<< orphan*/  physical_address_high; int /*<<< orphan*/  physical_address_low; scalar_t__ available_length; int /*<<< orphan*/  vpd; TYPE_1__ hdr; } ;
typedef  TYPE_2__ sli4_cmd_read_rev_t ;
struct TYPE_7__ {int /*<<< orphan*/  phys; scalar_t__ size; } ;
typedef  TYPE_3__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_READ_REV ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int32_t
sli_cmd_read_rev(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *vpd)
{
	sli4_cmd_read_rev_t	*read_rev = buf;

	ocs_memset(buf, 0, size);

	read_rev->hdr.command = SLI4_MBOX_COMMAND_READ_REV;

	if (vpd && vpd->size) {
		read_rev->vpd = TRUE;

		read_rev->available_length = vpd->size;

		read_rev->physical_address_low  = ocs_addr32_lo(vpd->phys);
		read_rev->physical_address_high = ocs_addr32_hi(vpd->phys);
	}

	return sizeof(sli4_cmd_read_rev_t);
}