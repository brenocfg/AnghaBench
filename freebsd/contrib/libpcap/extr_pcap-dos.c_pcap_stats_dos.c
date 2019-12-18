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
struct pcap_stat {scalar_t__ ps_ifdrop; int /*<<< orphan*/  ps_drop; int /*<<< orphan*/  ps_recv; } ;
struct pcap_dos {struct pcap_stat stat; } ;
struct net_device_stats {scalar_t__ rx_errors; scalar_t__ rx_dropped; scalar_t__ rx_missed_errors; int /*<<< orphan*/  rx_packets; } ;
struct device {struct net_device_stats* (* get_stats ) (struct device*) ;} ;
struct TYPE_3__ {struct pcap_dos* priv; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSHK () ; 
 struct device* get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct net_device_stats* stub1 (struct device*) ; 

__attribute__((used)) static int pcap_stats_dos (pcap_t *p, struct pcap_stat *ps)
{
  struct net_device_stats *stats;
  struct pcap_dos         *pd;
  struct device           *dev = p ? get_device(p->fd) : NULL;

  if (!dev)
  {
    strcpy (p->errbuf, "illegal pcap handle");
    return (-1);
  }

  if (!dev->get_stats || (stats = (*dev->get_stats)(dev)) == NULL)
  {
    strcpy (p->errbuf, "device statistics not available");
    return (-1);
  }

  FLUSHK();

  pd = p->priv;
  pd->stat.ps_recv   = stats->rx_packets;
  pd->stat.ps_drop  += stats->rx_missed_errors;
  pd->stat.ps_ifdrop = stats->rx_dropped +  /* queue full */
                         stats->rx_errors;    /* HW errors */
  if (ps)
     *ps = pd->stat;

  return (0);
}