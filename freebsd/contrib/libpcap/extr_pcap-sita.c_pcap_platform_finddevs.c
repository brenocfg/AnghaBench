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
struct TYPE_3__ {scalar_t__ beginning; } ;
typedef  TYPE_1__ pcap_if_list_t ;

/* Variables and functions */
 scalar_t__ acn_findalldevs (char*) ; 
 scalar_t__ acn_if_list ; 
 scalar_t__ acn_parse_hosts_file (char*) ; 
 scalar_t__* alldevsp ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int pcap_platform_finddevs(pcap_if_list_t *devlistp, char *errbuf) {

	//printf("pcap_findalldevs()\n");				// fulko

	*alldevsp = 0;												/* initialize the returned variables before we do anything */
	strcpy(errbuf, "");
	if (acn_parse_hosts_file(errbuf))							/* scan the hosts file for potential IOPs */
		{
		//printf("pcap_findalldevs() returning BAD after parsehosts\n");				// fulko
		return -1;
		}
	//printf("pcap_findalldevs() got hostlist now finding devs\n");				// fulko
	if (acn_findalldevs(errbuf))								/* then ask the IOPs for their monitorable devices */
		{
		//printf("pcap_findalldevs() returning BAD after findalldevs\n");				// fulko
		return -1;
		}
	devlistp->beginning = acn_if_list;
	acn_if_list = 0;											/* then forget our list head, because someone will call pcap_freealldevs() to empty the malloc'ed stuff */
	//printf("pcap_findalldevs() returning ZERO OK\n");				// fulko
	return 0;
}