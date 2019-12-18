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
typedef  int uint64_t ;
struct ntb_transport_qp {struct ntb_transport_ctx* transport; } ;
struct ntb_transport_ctx {int link_speed; int link_width; int /*<<< orphan*/  link_is_up; } ;

/* Variables and functions */
#define  NTB_SPEED_GEN1 131 
#define  NTB_SPEED_GEN2 130 
#define  NTB_SPEED_GEN3 129 
#define  NTB_SPEED_GEN4 128 

uint64_t
ntb_transport_link_speed(struct ntb_transport_qp *qp)
{
	struct ntb_transport_ctx *nt = qp->transport;
	uint64_t rate;

	if (!nt->link_is_up)
		return (0);
	switch (nt->link_speed) {
	case NTB_SPEED_GEN1:
		rate = 2500000000 * 8 / 10;
		break;
	case NTB_SPEED_GEN2:
		rate = 5000000000 * 8 / 10;
		break;
	case NTB_SPEED_GEN3:
		rate = 8000000000 * 128 / 130;
		break;
	case NTB_SPEED_GEN4:
		rate = 16000000000 * 128 / 130;
		break;
	default:
		return (0);
	}
	if (nt->link_width <= 0)
		return (0);
	return (rate * nt->link_width);
}