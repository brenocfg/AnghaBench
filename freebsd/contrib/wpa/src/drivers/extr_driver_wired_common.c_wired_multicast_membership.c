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
typedef  int /*<<< orphan*/  u8 ;
struct packet_mreq {int mr_ifindex; int /*<<< orphan*/  mr_address; int /*<<< orphan*/  mr_alen; int /*<<< orphan*/  mr_type; } ;
typedef  int /*<<< orphan*/  mreq ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  PACKET_ADD_MEMBERSHIP ; 
 int /*<<< orphan*/  PACKET_DROP_MEMBERSHIP ; 
 int /*<<< orphan*/  PACKET_MR_MULTICAST ; 
 int /*<<< orphan*/  SOL_PACKET ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct packet_mreq*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct packet_mreq*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int wired_multicast_membership(int sock, int ifindex, const u8 *addr, int add)
{
#ifdef __linux__
	struct packet_mreq mreq;

	if (sock < 0)
		return -1;

	os_memset(&mreq, 0, sizeof(mreq));
	mreq.mr_ifindex = ifindex;
	mreq.mr_type = PACKET_MR_MULTICAST;
	mreq.mr_alen = ETH_ALEN;
	os_memcpy(mreq.mr_address, addr, ETH_ALEN);

	if (setsockopt(sock, SOL_PACKET,
		       add ? PACKET_ADD_MEMBERSHIP : PACKET_DROP_MEMBERSHIP,
		       &mreq, sizeof(mreq)) < 0) {
		wpa_printf(MSG_ERROR, "setsockopt: %s", strerror(errno));
		return -1;
	}
	return 0;
#else /* __linux__ */
	return -1;
#endif /* __linux__ */
}