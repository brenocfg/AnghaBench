#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int (* read_op ) (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * rfile; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  pcap_handler ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_COUNT_IS_UNLIMITED (int) ; 
 int pcap_offline_read (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
pcap_loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
{
	register int n;

	for (;;) {
		if (p->rfile != NULL) {
			/*
			 * 0 means EOF, so don't loop if we get 0.
			 */
			n = pcap_offline_read(p, cnt, callback, user);
		} else {
			/*
			 * XXX keep reading until we get something
			 * (or an error occurs)
			 */
			do {
				n = p->read_op(p, cnt, callback, user);
			} while (n == 0);
		}
		if (n <= 0)
			return (n);
		if (!PACKET_COUNT_IS_UNLIMITED(cnt)) {
			cnt -= n;
			if (cnt <= 0)
				return (0);
		}
	}
}