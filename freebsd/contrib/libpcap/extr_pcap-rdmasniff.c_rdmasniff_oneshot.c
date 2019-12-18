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
typedef  int /*<<< orphan*/  u_char ;
struct pcap_rdmasniff {int /*<<< orphan*/  oneshot_buffer; } ;
struct pcap_pkthdr {int /*<<< orphan*/  caplen; } ;
struct oneshot_userdata {int /*<<< orphan*/ * pkt; struct pcap_pkthdr* hdr; TYPE_1__* pd; } ;
struct TYPE_2__ {struct pcap_rdmasniff* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rdmasniff_oneshot(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes)
{
	struct oneshot_userdata *sp = (struct oneshot_userdata *) user;
	pcap_t *handle = sp->pd;
	struct pcap_rdmasniff *priv = handle->priv;

	*sp->hdr = *h;
	memcpy(priv->oneshot_buffer, bytes, h->caplen);
	*sp->pkt = priv->oneshot_buffer;
}