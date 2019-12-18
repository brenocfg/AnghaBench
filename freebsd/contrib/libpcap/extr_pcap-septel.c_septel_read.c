#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_11__ {int /*<<< orphan*/  ps_recv; } ;
struct pcap_septel {TYPE_2__ stat; } ;
struct pcap_pkthdr {int caplen; unsigned short len; int /*<<< orphan*/  ts; } ;
struct TYPE_10__ {int /*<<< orphan*/ * bf_insns; } ;
struct TYPE_12__ {int snapshot; TYPE_1__ fcode; scalar_t__ break_loop; struct pcap_septel* priv; } ;
typedef  TYPE_3__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ;
struct TYPE_14__ {int type; } ;
struct TYPE_13__ {unsigned short len; } ;
typedef  TYPE_4__ MSG ;
typedef  TYPE_5__ HDR ;

/* Variables and functions */
 TYPE_5__* GCT_grab (unsigned int) ; 
 scalar_t__ bpf_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned short,int) ; 
 int /*<<< orphan*/ * get_param (TYPE_4__*) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relm (TYPE_5__*) ; 

__attribute__((used)) static int septel_read(pcap_t *p, int cnt, pcap_handler callback, u_char *user) {

  struct pcap_septel *ps = p->priv;
  HDR *h;
  MSG *m;
  int processed = 0 ;
  int t = 0 ;

  /* identifier for the message queue of the module(upe) from which we are capturing
   * packets.These IDs are defined in system.txt . By default it is set to 0x2d
   * so change it to 0xdd for technical reason and therefore the module id for upe becomes:
   * LOCAL        0xdd           * upe - Example user part task */
  unsigned int id = 0xdd;

  /* process the packets */
  do  {

    unsigned short packet_len = 0;
    int caplen = 0;
    int counter = 0;
    struct pcap_pkthdr   pcap_header;
    u_char *dp ;

    /*
     * Has "pcap_breakloop()" been called?
     */
loop:
    if (p->break_loop) {
      /*
       * Yes - clear the flag that indicates that
       * it has, and return -2 to indicate that
       * we were told to break out of the loop.
       */
      p->break_loop = 0;
      return -2;
    }

    /*repeat until a packet is read
     *a NULL message means :
     * when no packet is in queue or all packets in queue already read */
    do  {
      /* receive packet in non-blocking mode
       * GCT_grab is defined in the septel library software */
      h = GCT_grab(id);

      m = (MSG*)h;
      /* a couter is added here to avoid an infinite loop
       * that will cause our capture program GUI to freeze while waiting
       * for a packet*/
      counter++ ;

    }
    while  ((m == NULL)&& (counter< 100)) ;

    if (m != NULL) {

      t = h->type ;

      /* catch only messages with type = 0xcf00 or 0x8f01 corrsponding to ss7 messages*/
      /* XXX = why not use API_MSG_TX_REQ for 0xcf00 and API_MSG_RX_IND
       * for 0x8f01? */
      if ((t != 0xcf00) && (t != 0x8f01)) {
        relm(h);
        goto loop ;
      }

      /* XXX - is API_MSG_RX_IND for an MTP2 or MTP3 message? */
      dp = get_param(m);/* get pointer to MSG parameter area (m->param) */
      packet_len = m->len;
      caplen =  p->snapshot ;


      if (caplen > packet_len) {

        caplen = packet_len;
      }
      /* Run the packet filter if there is one. */
      if ((p->fcode.bf_insns == NULL) || bpf_filter(p->fcode.bf_insns, dp, packet_len, caplen)) {


        /*  get a time stamp , consisting of :
         *
         *  pcap_header.ts.tv_sec:
         *  ----------------------
         *   a UNIX format time-in-seconds when he packet was captured,
         *   i.e. the number of seconds since Epoch time (January 1,1970, 00:00:00 GMT)
         *
         *  pcap_header.ts.tv_usec :
         *  ------------------------
         *   the number of microseconds since that second
         *   when the packet was captured
         */

        (void)gettimeofday(&pcap_header.ts, NULL);

        /* Fill in our own header data */
        pcap_header.caplen = caplen;
        pcap_header.len = packet_len;

        /* Count the packet. */
        ps->stat.ps_recv++;

        /* Call the user supplied callback function */
        callback(user, &pcap_header, dp);

        processed++ ;

      }
      /* after being processed the packet must be
       *released in order to receive another one */
      relm(h);
    }else
      processed++;

  }
  while (processed < cnt) ;

  return processed ;
}