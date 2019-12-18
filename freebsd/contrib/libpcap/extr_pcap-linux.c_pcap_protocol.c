#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int protocol; } ;
struct TYPE_5__ {TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int ETH_P_ALL ; 
 int htons (int) ; 

__attribute__((used)) static int pcap_protocol(pcap_t *handle)
{
	int protocol;

	protocol = handle->opt.protocol;
	if (protocol == 0)
		protocol = ETH_P_ALL;

	return htons(protocol);
}