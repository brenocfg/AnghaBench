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
struct tws_request {TYPE_2__* cmd_pkt; int /*<<< orphan*/  error_code; int /*<<< orphan*/  request_id; int /*<<< orphan*/  sc; } ;
struct TYPE_3__ {int /*<<< orphan*/  error; } ;
struct tws_command_header {TYPE_1__ status_block; } ;
struct TYPE_4__ {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWS_TRACE_DEBUG (int /*<<< orphan*/ ,char*,struct tws_command_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct tws_command_header*,int) ; 
 int /*<<< orphan*/  tws_passthru_complete (struct tws_request*) ; 

__attribute__((used)) static void
tws_passthru_err_complete(struct tws_request *req, 
                                          struct tws_command_header *hdr)
{ 
    TWS_TRACE_DEBUG(req->sc, "entry", hdr, req->request_id);
    req->error_code = hdr->status_block.error;
    memcpy(&(req->cmd_pkt->hdr), hdr, sizeof(struct tws_command_header));
    tws_passthru_complete(req);
}