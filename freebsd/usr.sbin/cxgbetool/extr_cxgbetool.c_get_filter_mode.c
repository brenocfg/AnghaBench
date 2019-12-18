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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_GET_FILTER_MODE ; 
 int T4_FILTER_ETH_TYPE ; 
 int T4_FILTER_FCoE ; 
 int T4_FILTER_IC_VNIC ; 
 int T4_FILTER_IP_DADDR ; 
 int T4_FILTER_IP_DPORT ; 
 int T4_FILTER_IP_FRAGMENT ; 
 int T4_FILTER_IP_PROTO ; 
 int T4_FILTER_IP_SADDR ; 
 int T4_FILTER_IP_SPORT ; 
 int T4_FILTER_IP_TOS ; 
 int T4_FILTER_IPv4 ; 
 int T4_FILTER_IPv6 ; 
 int T4_FILTER_MAC_IDX ; 
 int T4_FILTER_MPS_HIT_TYPE ; 
 int T4_FILTER_PORT ; 
 int T4_FILTER_VLAN ; 
 int T4_FILTER_VNIC ; 
 int doit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
get_filter_mode(int hashfilter)
{
	uint32_t mode = hashfilter;
	int rc;

	rc = doit(CHELSIO_T4_GET_FILTER_MODE, &mode);
	if (rc != 0)
		return (rc);

	if (mode & T4_FILTER_IPv4)
		printf("ipv4 ");

	if (mode & T4_FILTER_IPv6)
		printf("ipv6 ");

	if (mode & T4_FILTER_IP_SADDR)
		printf("sip ");

	if (mode & T4_FILTER_IP_DADDR)
		printf("dip ");

	if (mode & T4_FILTER_IP_SPORT)
		printf("sport ");

	if (mode & T4_FILTER_IP_DPORT)
		printf("dport ");

	if (mode & T4_FILTER_IP_FRAGMENT)
		printf("frag ");

	if (mode & T4_FILTER_MPS_HIT_TYPE)
		printf("matchtype ");

	if (mode & T4_FILTER_MAC_IDX)
		printf("macidx ");

	if (mode & T4_FILTER_ETH_TYPE)
		printf("ethtype ");

	if (mode & T4_FILTER_IP_PROTO)
		printf("proto ");

	if (mode & T4_FILTER_IP_TOS)
		printf("tos ");

	if (mode & T4_FILTER_VLAN)
		printf("vlan ");

	if (mode & T4_FILTER_VNIC) {
		if (mode & T4_FILTER_IC_VNIC)
			printf("vnic_id ");
		else
			printf("ovlan ");
	}

	if (mode & T4_FILTER_PORT)
		printf("iport ");

	if (mode & T4_FILTER_FCoE)
		printf("fcoe ");

	printf("\n");

	return (0);
}