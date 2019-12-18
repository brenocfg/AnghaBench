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
struct fw_request {int dummy; } ;
struct fw_card {int /*<<< orphan*/ * topology_map; } ;
struct TYPE_2__ {unsigned long long start; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCODE_ADDRESS_ERROR ; 
 int /*<<< orphan*/  RCODE_COMPLETE ; 
 int /*<<< orphan*/  RCODE_TYPE_ERROR ; 
 int /*<<< orphan*/  TCODE_IS_READ_REQUEST (int) ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__ topology_map_region ; 

__attribute__((used)) static void handle_topology_map(struct fw_card *card, struct fw_request *request,
		int tcode, int destination, int source, int generation,
		unsigned long long offset, void *payload, size_t length,
		void *callback_data)
{
	int start;

	if (!TCODE_IS_READ_REQUEST(tcode)) {
		fw_send_response(card, request, RCODE_TYPE_ERROR);
		return;
	}

	if ((offset & 3) > 0 || (length & 3) > 0) {
		fw_send_response(card, request, RCODE_ADDRESS_ERROR);
		return;
	}

	start = (offset - topology_map_region.start) / 4;
	memcpy(payload, &card->topology_map[start], length);

	fw_send_response(card, request, RCODE_COMPLETE);
}