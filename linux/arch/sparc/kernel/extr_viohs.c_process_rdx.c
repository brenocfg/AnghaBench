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
struct TYPE_2__ {int stype; } ;
struct vio_rdx {TYPE_1__ tag; } ;
struct vio_driver_state {int dummy; } ;

/* Variables and functions */
#define  VIO_SUBTYPE_ACK 130 
#define  VIO_SUBTYPE_INFO 129 
#define  VIO_SUBTYPE_NACK 128 
 int /*<<< orphan*/  all_drings_registered (struct vio_driver_state*) ; 
 int handshake_failure (struct vio_driver_state*) ; 
 int process_rdx_ack (struct vio_driver_state*,struct vio_rdx*) ; 
 int process_rdx_info (struct vio_driver_state*,struct vio_rdx*) ; 
 int process_rdx_nack (struct vio_driver_state*,struct vio_rdx*) ; 

__attribute__((used)) static int process_rdx(struct vio_driver_state *vio, struct vio_rdx *pkt)
{
	if (!all_drings_registered(vio))
		handshake_failure(vio);

	switch (pkt->tag.stype) {
	case VIO_SUBTYPE_INFO:
		return process_rdx_info(vio, pkt);

	case VIO_SUBTYPE_ACK:
		return process_rdx_ack(vio, pkt);

	case VIO_SUBTYPE_NACK:
		return process_rdx_nack(vio, pkt);

	default:
		return handshake_failure(vio);
	}
}