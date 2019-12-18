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
struct pcap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcap_close (struct pcap*) ; 
 struct pcap* pcaps_to_close ; 

__attribute__((used)) static void
pcap_close_all(void)
{
	struct pcap *handle;

	while ((handle = pcaps_to_close) != NULL)
		pcap_close(handle);
}