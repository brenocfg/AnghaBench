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
struct pcap_stat_ex {int dummy; } ;
struct device {int /*<<< orphan*/  (* get_stats ) (struct device*) ;int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 struct device* get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct pcap_stat_ex*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strnicmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 

int pcap_stats_ex (pcap_t *p, struct pcap_stat_ex *se)
{
  struct device *dev = p ? get_device (p->fd) : NULL;

  if (!dev || !dev->get_stats)
  {
    strlcpy (p->errbuf, "detailed device statistics not available",
             PCAP_ERRBUF_SIZE);
    return (-1);
  }

  if (!strnicmp(dev->name,"pkt",3))
  {
    strlcpy (p->errbuf, "pktdrvr doesn't have detailed statistics",
             PCAP_ERRBUF_SIZE);
    return (-1);
  }
  memcpy (se, (*dev->get_stats)(dev), sizeof(*se));
  return (0);
}