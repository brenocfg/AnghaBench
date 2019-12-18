#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcap_dlpi {int send_fd; } ;
struct TYPE_4__ {struct pcap_dlpi* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_1__*) ; 

__attribute__((used)) static void
pcap_cleanup_dlpi(pcap_t *p)
{
#ifdef DL_HP_RAWDLS
	struct pcap_dlpi *pd = p->priv;

	if (pd->send_fd >= 0) {
		close(pd->send_fd);
		pd->send_fd = -1;
	}
#endif
	pcap_cleanup_live_common(p);
}