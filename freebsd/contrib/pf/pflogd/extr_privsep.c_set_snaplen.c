#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int snapshot; } ;

/* Variables and functions */
 TYPE_1__* hpcap ; 
 int /*<<< orphan*/  set_pcap_filter () ; 

__attribute__((used)) static int
set_snaplen(int snap)
{
	if (hpcap == NULL)
		return (1);

	hpcap->snapshot = snap;
	set_pcap_filter();

	return 0;
}