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
typedef  int /*<<< orphan*/  uint16_t ;
struct input {int cmpl_ring; int target_id; int /*<<< orphan*/  resp_addr; int /*<<< orphan*/  req_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  idi_paddr; } ;
struct bnxt_softc {TYPE_1__ hwrm_cmd_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_hwrm_cmd_hdr_init(struct bnxt_softc *softc, void *request,
    uint16_t req_type)
{
	struct input *req = request;

	req->req_type = htole16(req_type);
	req->cmpl_ring = 0xffff;
	req->target_id = 0xffff;
	req->resp_addr = htole64(softc->hwrm_cmd_resp.idi_paddr);
}