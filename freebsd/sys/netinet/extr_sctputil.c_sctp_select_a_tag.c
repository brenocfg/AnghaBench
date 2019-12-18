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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct timeval {int dummy; } ;
struct sctp_inpcb {int /*<<< orphan*/  sctp_ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_GETTIME_TIMEVAL (struct timeval*) ; 
 scalar_t__ sctp_is_vtag_good (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*) ; 
 scalar_t__ sctp_select_initial_TSN (int /*<<< orphan*/ *) ; 

uint32_t
sctp_select_a_tag(struct sctp_inpcb *inp, uint16_t lport, uint16_t rport, int check)
{
	uint32_t x;
	struct timeval now;

	if (check) {
		(void)SCTP_GETTIME_TIMEVAL(&now);
	}
	for (;;) {
		x = sctp_select_initial_TSN(&inp->sctp_ep);
		if (x == 0) {
			/* we never use 0 */
			continue;
		}
		if (!check || sctp_is_vtag_good(x, lport, rport, &now)) {
			break;
		}
	}
	return (x);
}