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
struct ntb_transport_qp {unsigned int tx_max_frame; } ;
struct ntb_payload_header {int dummy; } ;

/* Variables and functions */

unsigned int
ntb_transport_max_size(struct ntb_transport_qp *qp)
{

	return (qp->tx_max_frame - sizeof(struct ntb_payload_header));
}