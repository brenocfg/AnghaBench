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
struct TYPE_3__ {struct pcap_win* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/ * PAirpcapHandle ;

/* Variables and functions */
 int /*<<< orphan*/ * PacketGetAirPcapHandle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PAirpcapHandle
pcap_get_airpcap_handle_npf(pcap_t *p)
{
#ifdef HAVE_AIRPCAP_API
	struct pcap_win *pw = p->priv;

	return (PacketGetAirPcapHandle(pw->adapter));
#else
	return (NULL);
#endif /* HAVE_AIRPCAP_API */
}