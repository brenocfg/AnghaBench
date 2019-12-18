#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  errbuf; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  pcap_direction_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int pcap_setdirection_acn(pcap_t *handle, pcap_direction_t d) {
	pcap_snprintf(handle->errbuf, sizeof(handle->errbuf),
	    "Setting direction is not supported on ACN adapters");
	return -1;
}