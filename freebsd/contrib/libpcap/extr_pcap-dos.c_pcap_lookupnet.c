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
typedef  int /*<<< orphan*/  bpf_u_int32 ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (char const*) ; 
 scalar_t__ IN_CLASSA (int /*<<< orphan*/ ) ; 
 int IN_CLASSA_NET ; 
 scalar_t__ IN_CLASSB (int /*<<< orphan*/ ) ; 
 int IN_CLASSB_NET ; 
 scalar_t__ IN_CLASSC (int /*<<< orphan*/ ) ; 
 int IN_CLASSC_NET ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int _w32_sin_mask ; 
 int /*<<< orphan*/  _watt_is_init ; 
 int /*<<< orphan*/  htonl (int) ; 
 int my_ip_addr ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int pcap_lookupnet (const char *device, bpf_u_int32 *localnet,
                    bpf_u_int32 *netmask, char *errbuf)
{
  DWORD mask, net;

  if (!_watt_is_init)
  {
    strcpy (errbuf, "pcap_open_offline() or pcap_activate() must be "
                    "called first");
    return (-1);
  }

  mask  = _w32_sin_mask;
  net = my_ip_addr & mask;
  if (net == 0)
  {
    if (IN_CLASSA(*netmask))
       net = IN_CLASSA_NET;
    else if (IN_CLASSB(*netmask))
       net = IN_CLASSB_NET;
    else if (IN_CLASSC(*netmask))
       net = IN_CLASSC_NET;
    else
    {
      pcap_snprintf (errbuf, PCAP_ERRBUF_SIZE, "inet class for 0x%lx unknown", mask);
      return (-1);
    }
  }
  *localnet = htonl (net);
  *netmask = htonl (mask);

  ARGSUSED (device);
  return (0);
}