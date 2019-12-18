#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  device; int /*<<< orphan*/  promisc; scalar_t__ rfmon; } ;
struct TYPE_8__ {scalar_t__ snapshot; int fd; TYPE_1__ opt; int /*<<< orphan*/  errbuf; scalar_t__ bufsize; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * setdirection_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  inject_op; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  read_op; int /*<<< orphan*/  cleanup_op; int /*<<< orphan*/  linktype; } ;
typedef  TYPE_2__ pcap_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_EN10MB ; 
 scalar_t__ ETH_MAX ; 
 scalar_t__ ETH_MIN ; 
 scalar_t__ MAXIMUM_SNAPLEN ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_RFMON_NOTSUP ; 
 TYPE_5__* active_dev ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  close_driver ; 
 int /*<<< orphan*/  first_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__** handle_to_device ; 
 int /*<<< orphan*/  init_watt32 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_cleanup_dos ; 
 int /*<<< orphan*/  pcap_read_dos ; 
 int /*<<< orphan*/  pcap_sendpacket_dos ; 
 int /*<<< orphan*/  pcap_setfilter_dos ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_stats_dos ; 
 int ref_count ; 
 scalar_t__ stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcap_activate_dos (pcap_t *pcap)
{
  if (pcap->opt.rfmon) {
    /*
     * No monitor mode on DOS.
     */
    return (PCAP_ERROR_RFMON_NOTSUP);
  }

  /*
   * Turn a negative snapshot value (invalid), a snapshot value of
   * 0 (unspecified), or a value bigger than the normal maximum
   * value, into the maximum allowed value.
   *
   * If some application really *needs* a bigger snapshot
   * length, we should just increase MAXIMUM_SNAPLEN.
   */
  if (pcap->snapshot <= 0 || pcap->snapshot > MAXIMUM_SNAPLEN)
    pcap->snapshot = MAXIMUM_SNAPLEN;

  if (pcap->snapshot < ETH_MIN+8)
      pcap->snapshot = ETH_MIN+8;

  if (pcap->snapshot > ETH_MAX)   /* silently accept and truncate large MTUs */
      pcap->snapshot = ETH_MAX;

  pcap->linktype          = DLT_EN10MB;  /* !! */
  pcap->cleanup_op        = pcap_cleanup_dos;
  pcap->read_op           = pcap_read_dos;
  pcap->stats_op          = pcap_stats_dos;
  pcap->inject_op         = pcap_sendpacket_dos;
  pcap->setfilter_op      = pcap_setfilter_dos;
  pcap->setdirection_op   = NULL;  /* Not implemented.*/
  pcap->fd                = ++ref_count;

  pcap->bufsize = ETH_MAX+100;     /* add some margin */
  pcap->buffer = calloc (pcap->bufsize, 1);

  if (pcap->fd == 1)  /* first time we're called */
  {
    if (!init_watt32(pcap, pcap->opt.device, pcap->errbuf) ||
        !first_init(pcap->opt.device, pcap->errbuf, pcap->opt.promisc))
    {
      /* XXX - free pcap->buffer? */
      return (PCAP_ERROR);
    }
    atexit (close_driver);
  }
  else if (stricmp(active_dev->name,pcap->opt.device))
  {
    pcap_snprintf (pcap->errbuf, PCAP_ERRBUF_SIZE,
                   "Cannot use different devices simultaneously "
                   "(`%s' vs. `%s')", active_dev->name, pcap->opt.device);
    /* XXX - free pcap->buffer? */
    return (PCAP_ERROR);
  }
  handle_to_device [pcap->fd-1] = active_dev;
  return (0);
}