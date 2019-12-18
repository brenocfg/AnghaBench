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
struct sockaddr_ll {int dummy; } ;
struct ifreq {int dummy; } ;
typedef  int /*<<< orphan*/  pcap_t ;
typedef  int /*<<< orphan*/  mask ;

/* Variables and functions */
 int PACKET_BROADCAST ; 
 int /*<<< orphan*/  PACKET_RECV_TYPE ; 
 int /*<<< orphan*/  SOL_PACKET ; 
 int pcap_get_selectable_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
set_recv_type(pcap_t *p, bool rx)
{
#ifdef PACKET_RECV_TYPE
	struct sockaddr_ll sll;
	struct ifreq ifr;
	int mask;
	int fd;

	fd = pcap_get_selectable_fd(p);
	if (fd < 0)
		return;

	if (rx)
		mask = 1 << PACKET_BROADCAST;
	else
		mask = 0;

	setsockopt(fd, SOL_PACKET, PACKET_RECV_TYPE, &mask, sizeof(mask));
#endif
}