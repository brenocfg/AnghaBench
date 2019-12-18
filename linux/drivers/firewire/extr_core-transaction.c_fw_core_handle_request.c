#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct fw_request {int /*<<< orphan*/  length; } ;
struct fw_packet {scalar_t__ ack; int* header; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACK_COMPLETE ; 
 scalar_t__ ACK_PENDING ; 
 scalar_t__ HEADER_GET_OFFSET_HIGH (int) ; 
 int /*<<< orphan*/  HEADER_GET_TCODE (int) ; 
 scalar_t__ TCODE_IS_LINK_INTERNAL (int /*<<< orphan*/ ) ; 
 struct fw_request* allocate_request (struct fw_card*,struct fw_packet*) ; 
 int /*<<< orphan*/  fw_cdev_handle_phy_packet (struct fw_card*,struct fw_packet*) ; 
 int /*<<< orphan*/  handle_exclusive_region_request (struct fw_card*,struct fw_packet*,struct fw_request*,unsigned long long) ; 
 int /*<<< orphan*/  handle_fcp_region_request (struct fw_card*,struct fw_packet*,struct fw_request*,unsigned long long) ; 
 int /*<<< orphan*/  is_in_fcp_region (unsigned long long,int /*<<< orphan*/ ) ; 

void fw_core_handle_request(struct fw_card *card, struct fw_packet *p)
{
	struct fw_request *request;
	unsigned long long offset;

	if (p->ack != ACK_PENDING && p->ack != ACK_COMPLETE)
		return;

	if (TCODE_IS_LINK_INTERNAL(HEADER_GET_TCODE(p->header[0]))) {
		fw_cdev_handle_phy_packet(card, p);
		return;
	}

	request = allocate_request(card, p);
	if (request == NULL) {
		/* FIXME: send statically allocated busy packet. */
		return;
	}

	offset = ((u64)HEADER_GET_OFFSET_HIGH(p->header[1]) << 32) |
		p->header[2];

	if (!is_in_fcp_region(offset, request->length))
		handle_exclusive_region_request(card, p, request, offset);
	else
		handle_fcp_region_request(card, p, request, offset);

}