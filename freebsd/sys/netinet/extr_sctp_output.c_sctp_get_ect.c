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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int ecn_supported; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_ECT0_BIT ; 

__attribute__((used)) static uint8_t
sctp_get_ect(struct sctp_tcb *stcb)
{
	if ((stcb != NULL) && (stcb->asoc.ecn_supported == 1)) {
		return (SCTP_ECT0_BIT);
	} else {
		return (0);
	}
}