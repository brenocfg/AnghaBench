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
struct pcap_stat {int dummy; } ;
struct pcap_septel {struct pcap_stat stat; } ;
struct TYPE_3__ {struct pcap_septel* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */

__attribute__((used)) static int septel_stats(pcap_t *p, struct pcap_stat *ps) {
  struct pcap_septel *handlep = p->priv;
  /*handlep->stat.ps_recv = 0;*/
  /*handlep->stat.ps_drop = 0;*/

  *ps = handlep->stat;

  return 0;
}