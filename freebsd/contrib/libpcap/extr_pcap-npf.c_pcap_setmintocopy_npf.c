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
struct pcap_win {int /*<<< orphan*/  adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; struct pcap_win* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 scalar_t__ PacketSetMinToCopy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
pcap_setmintocopy_npf(pcap_t *p, int size)
{
	struct pcap_win *pw = p->priv;

	if(PacketSetMinToCopy(pw->adapter, size)==FALSE)
	{
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "driver error: unable to set the requested mintocopy size");
		return (-1);
	}
	return (0);
}