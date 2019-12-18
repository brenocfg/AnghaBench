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
typedef  void* uint32_t ;
struct TYPE_4__ {void* version; void* request_length; void* timeout; void* domain; void* port_number; void* subsystem; void* opcode; } ;
struct TYPE_3__ {TYPE_2__ req; } ;
struct mbx_hdr {TYPE_1__ u0; } ;

/* Variables and functions */

void
mbx_common_req_hdr_init(struct mbx_hdr *hdr,
			uint8_t dom, uint8_t port,
			uint8_t subsys, uint8_t opcode,
			uint32_t timeout, uint32_t pyld_len,
			uint8_t version)
{
	hdr->u0.req.opcode = opcode;
	hdr->u0.req.subsystem = subsys;
	hdr->u0.req.port_number = port;
	hdr->u0.req.domain = dom;

	hdr->u0.req.timeout = timeout;
	hdr->u0.req.request_length = pyld_len - sizeof(struct mbx_hdr);
	hdr->u0.req.version = version;
}