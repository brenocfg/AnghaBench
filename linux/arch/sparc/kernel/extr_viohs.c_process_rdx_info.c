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
struct TYPE_2__ {int /*<<< orphan*/  stype; } ;
struct vio_rdx {TYPE_1__ tag; } ;
struct vio_driver_state {int /*<<< orphan*/  hs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int /*<<< orphan*/  VIO_HS_SENT_RDX_ACK ; 
 int /*<<< orphan*/  VIO_SUBTYPE_ACK ; 
 int handshake_failure (struct vio_driver_state*) ; 
 scalar_t__ send_ctrl (struct vio_driver_state*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int process_rdx_info(struct vio_driver_state *vio, struct vio_rdx *pkt)
{
	viodbg(HS, "GOT RDX INFO\n");

	pkt->tag.stype = VIO_SUBTYPE_ACK;
	viodbg(HS, "SEND RDX ACK\n");
	if (send_ctrl(vio, &pkt->tag, sizeof(*pkt)) < 0)
		return handshake_failure(vio);

	vio->hs_state |= VIO_HS_SENT_RDX_ACK;
	return 0;
}