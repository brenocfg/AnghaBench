#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union el_timestamp {int /*<<< orphan*/  as_int; } ;
struct TYPE_9__ {int frame_length; } ;
struct TYPE_8__ {int frame_length; int frame_packet_count; union el_timestamp timestamp; } ;
struct TYPE_7__ {int frame_length; int frame_packet_count; union el_timestamp timestamp; } ;
struct TYPE_6__ {int frame_length; int frame_packet_count; } ;
struct TYPE_10__ {TYPE_4__ logout_header; TYPE_3__ err_halt; TYPE_2__ sys_event; TYPE_1__ sys_err; } ;
struct el_subpacket {unsigned long length; int /*<<< orphan*/  type; int /*<<< orphan*/  class; TYPE_5__ by_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_CLASS__HEADER ; 
#define  EL_TYPE__HEADER__HALT_FRAME 131 
#define  EL_TYPE__HEADER__LOGOUT_FRAME 130 
#define  EL_TYPE__HEADER__SYSTEM_ERROR_FRAME 129 
#define  EL_TYPE__HEADER__SYSTEM_EVENT_FRAME 128 
 int /*<<< orphan*/  el_print_timestamp (union el_timestamp*) ; 
 int /*<<< orphan*/  el_process_subpackets (struct el_subpacket*,int) ; 
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static struct el_subpacket *
el_process_header_subpacket(struct el_subpacket *header)
{
	union el_timestamp timestamp;
	char *name = "UNKNOWN EVENT";
	int packet_count = 0;
	int length = 0;

	if (header->class != EL_CLASS__HEADER) {
		printk("%s** Unexpected header CLASS %d TYPE %d, aborting\n",
		       err_print_prefix,
		       header->class, header->type);
		return NULL;
	}

	switch(header->type) {
	case EL_TYPE__HEADER__SYSTEM_ERROR_FRAME:
		name = "SYSTEM ERROR";
		length = header->by_type.sys_err.frame_length;
		packet_count = 
			header->by_type.sys_err.frame_packet_count;
		timestamp.as_int = 0;
		break;
	case EL_TYPE__HEADER__SYSTEM_EVENT_FRAME:
		name = "SYSTEM EVENT";
		length = header->by_type.sys_event.frame_length;
		packet_count = 
			header->by_type.sys_event.frame_packet_count;
		timestamp = header->by_type.sys_event.timestamp;
		break;
	case EL_TYPE__HEADER__HALT_FRAME:
		name = "ERROR HALT";
		length = header->by_type.err_halt.frame_length;
		packet_count = 
			header->by_type.err_halt.frame_packet_count;
		timestamp = header->by_type.err_halt.timestamp;
		break;
	case EL_TYPE__HEADER__LOGOUT_FRAME:
		name = "LOGOUT FRAME";
		length = header->by_type.logout_header.frame_length;
		packet_count = 1;
		timestamp.as_int = 0;
		break;
	default: /* Unknown */
		printk("%s** Unknown header - CLASS %d TYPE %d, aborting\n",
		       err_print_prefix,
		       header->class, header->type);
		return NULL;		
	}

	printk("%s*** %s:\n"
	         "  CLASS %d, TYPE %d\n", 
	       err_print_prefix,
	       name,
	       header->class, header->type);
	el_print_timestamp(&timestamp);
	
	/*
	 * Process the subpackets
	 */
	el_process_subpackets(header, packet_count);

	/* return the next header */
	header = (struct el_subpacket *)
		((unsigned long)header + header->length + length);
	return header;
}