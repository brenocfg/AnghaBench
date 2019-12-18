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
struct ldc_packet {int stype; } ;
struct ldc_channel {int dummy; } ;

/* Variables and functions */
 int LDC_ABORT (struct ldc_channel*) ; 
 int LDC_ACK ; 
 int LDC_NACK ; 
 int process_data_ack (struct ldc_channel*,struct ldc_packet*) ; 

__attribute__((used)) static int data_ack_nack(struct ldc_channel *lp, struct ldc_packet *p)
{
	if (p->stype & LDC_ACK) {
		int err = process_data_ack(lp, p);
		if (err)
			return err;
	}
	if (p->stype & LDC_NACK)
		return LDC_ABORT(lp);

	return 0;
}