#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  subpacket_count; int /*<<< orphan*/  halt_code; int /*<<< orphan*/  exc_addr; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  rbox_whami; int /*<<< orphan*/  whami; } ;
struct TYPE_8__ {TYPE_3__ logout; } ;
struct ev7_pal_subpacket {TYPE_4__ by_type; } ;
struct TYPE_5__ {scalar_t__ data_start; } ;
struct TYPE_6__ {TYPE_1__ raw; } ;
struct el_subpacket {scalar_t__ class; int type; scalar_t__ length; TYPE_2__ by_type; } ;

/* Variables and functions */
 scalar_t__ EL_CLASS__PAL ; 
#define  EL_TYPE__PAL__LOGOUT_FRAME 128 
 int /*<<< orphan*/  el_annotate_subpacket (struct el_subpacket*) ; 
 int /*<<< orphan*/  el_print_timestamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  el_process_subpackets (struct el_subpacket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static struct el_subpacket *
ev7_process_pal_subpacket(struct el_subpacket *header)
{
	struct ev7_pal_subpacket *packet;

	if (header->class != EL_CLASS__PAL) {
		printk("%s  ** Unexpected header CLASS %d TYPE %d, aborting\n",
		       err_print_prefix,
		       header->class, header->type);
		return NULL;
	}

	packet = (struct ev7_pal_subpacket *)header->by_type.raw.data_start;

	switch(header->type) {
	case EL_TYPE__PAL__LOGOUT_FRAME:
		printk("%s*** MCHK occurred on LPID %lld (RBOX %llx)\n",
		       err_print_prefix,
		       packet->by_type.logout.whami, 
		       packet->by_type.logout.rbox_whami);
		el_print_timestamp(&packet->by_type.logout.timestamp);
		printk("%s  EXC_ADDR: %016llx\n"
		         "  HALT_CODE: %llx\n",
		       err_print_prefix,
		       packet->by_type.logout.exc_addr,
		       packet->by_type.logout.halt_code);
		el_process_subpackets(header,
                                      packet->by_type.logout.subpacket_count);
		break;
	default:
		printk("%s  ** PAL TYPE %d SUBPACKET\n", 
		       err_print_prefix,
		       header->type);
		el_annotate_subpacket(header);
		break;
	}
	
	return (struct el_subpacket *)((unsigned long)header + header->length);
}