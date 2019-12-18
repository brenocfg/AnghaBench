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
struct fw_request {scalar_t__ ack; int /*<<< orphan*/  response; int /*<<< orphan*/ * request_header; int /*<<< orphan*/ * data; } ;
struct fw_card {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_response ) (struct fw_card*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ ACK_PENDING ; 
 scalar_t__ HEADER_DESTINATION_IS_BROADCAST (int /*<<< orphan*/ ) ; 
 int RCODE_COMPLETE ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  fw_fill_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_get_response_length (struct fw_request*) ; 
 int /*<<< orphan*/  kfree (struct fw_request*) ; 
 int /*<<< orphan*/  stub1 (struct fw_card*,int /*<<< orphan*/ *) ; 

void fw_send_response(struct fw_card *card,
		      struct fw_request *request, int rcode)
{
	if (WARN_ONCE(!request, "invalid for FCP address handlers"))
		return;

	/* unified transaction or broadcast transaction: don't respond */
	if (request->ack != ACK_PENDING ||
	    HEADER_DESTINATION_IS_BROADCAST(request->request_header[0])) {
		kfree(request);
		return;
	}

	if (rcode == RCODE_COMPLETE)
		fw_fill_response(&request->response, request->request_header,
				 rcode, request->data,
				 fw_get_response_length(request));
	else
		fw_fill_response(&request->response, request->request_header,
				 rcode, NULL, 0);

	card->driver->send_response(card, &request->response);
}