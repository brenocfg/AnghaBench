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
 int IBV_RAW_PACKET_CAP_CVLAN_STRIPPING ; 
 int IBV_RAW_PACKET_CAP_IP_CSUM ; 
 int IBV_RAW_PACKET_CAP_SCATTER_FCS ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void print_raw_packet_caps(uint32_t raw_packet_caps)
{
	printf("\traw packet caps:\n");
	if (raw_packet_caps & IBV_RAW_PACKET_CAP_CVLAN_STRIPPING)
		printf("\t\t\t\t\tC-VLAN stripping offload\n");
	if (raw_packet_caps & IBV_RAW_PACKET_CAP_SCATTER_FCS)
		printf("\t\t\t\t\tScatter FCS offload\n");
	if (raw_packet_caps & IBV_RAW_PACKET_CAP_IP_CSUM)
		printf("\t\t\t\t\tIP csum offload\n");
}