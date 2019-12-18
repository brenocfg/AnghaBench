#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_18__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  fsm; } ;
struct TYPE_32__ {int /*<<< orphan*/  total; } ;
struct TYPE_23__ {TYPE_18__ ccp; TYPE_7__ stats; int /*<<< orphan*/  proto_out; int /*<<< orphan*/  proto_in; int /*<<< orphan*/  Queue; } ;
struct TYPE_20__ {int /*<<< orphan*/  sun_path; } ;
struct TYPE_19__ {struct datalink* dl; } ;
struct TYPE_24__ {TYPE_11__ socket; TYPE_10__ send; } ;
struct TYPE_26__ {int /*<<< orphan*/  len; int /*<<< orphan*/  address; int /*<<< orphan*/  class; } ;
struct TYPE_22__ {TYPE_1__ enddisc; int /*<<< orphan*/  authname; } ;
struct TYPE_34__ {scalar_t__ next_in; scalar_t__ min_in; } ;
struct TYPE_33__ {int /*<<< orphan*/  af; scalar_t__ link; scalar_t__ seq; } ;
struct TYPE_27__ {int /*<<< orphan*/  period; } ;
struct TYPE_28__ {TYPE_2__ autoload; } ;
struct mp {int active; scalar_t__ local_mrru; scalar_t__ peer_mrru; scalar_t__ local_is12bit; scalar_t__ peer_is12bit; TYPE_15__ link; TYPE_12__* bundle; TYPE_16__ server; TYPE_13__ peer; TYPE_9__ seq; TYPE_8__ out; TYPE_3__ cfg; } ;
struct lcp {scalar_t__ want_mrru; scalar_t__ his_mrru; scalar_t__ want_shortseq; scalar_t__ his_shortseq; } ;
struct datalink {int /*<<< orphan*/  name; TYPE_6__* physical; TYPE_13__ peer; } ;
struct TYPE_29__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_30__ {TYPE_4__ stats; struct lcp lcp; } ;
struct TYPE_31__ {TYPE_5__ link; } ;
struct TYPE_21__ {int /*<<< orphan*/  ncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  LogPHASE ; 
#define  MPSERVER_CONNECTED 130 
#define  MPSERVER_FAILED 129 
#define  MPSERVER_LISTENING 128 
 int MP_ADDED ; 
 int MP_FAILED ; 
 int MP_LINKSENT ; 
 int MP_UP ; 
 int /*<<< orphan*/  ccp_SetOpenMode (TYPE_18__*) ; 
 int /*<<< orphan*/  fsm_Open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_Up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  mp_Enddisc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_UpDown ; 
 int mpserver_Open (TYPE_16__*,TYPE_13__*) ; 
 int /*<<< orphan*/  ncp_SetLink (int /*<<< orphan*/ *,TYPE_15__*) ; 
 int /*<<< orphan*/  peerid_Equal (TYPE_13__*,TYPE_13__*) ; 
 int /*<<< orphan*/  throughput_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mp*) ; 
 int /*<<< orphan*/  throughput_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throughput_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
mp_Up(struct mp *mp, struct datalink *dl)
{
  struct lcp *lcp = &dl->physical->link.lcp;

  if (mp->active) {
    /* We're adding a link - do a last validation on our parameters */
    if (!peerid_Equal(&dl->peer, &mp->peer)) {
      log_Printf(LogPHASE, "%s: Inappropriate peer !\n", dl->name);
      log_Printf(LogPHASE, "  Attached to peer %s/%s\n", mp->peer.authname,
                 mp_Enddisc(mp->peer.enddisc.class, mp->peer.enddisc.address,
                            mp->peer.enddisc.len));
      log_Printf(LogPHASE, "  New link is peer %s/%s\n", dl->peer.authname,
                 mp_Enddisc(dl->peer.enddisc.class, dl->peer.enddisc.address,
                            dl->peer.enddisc.len));
      return MP_FAILED;
    }
    if (mp->local_mrru != lcp->want_mrru ||
        mp->peer_mrru != lcp->his_mrru ||
        mp->local_is12bit != lcp->want_shortseq ||
        mp->peer_is12bit != lcp->his_shortseq) {
      log_Printf(LogPHASE, "%s: Invalid MRRU/SHORTSEQ MP parameters !\n",
                dl->name);
      return MP_FAILED;
    }
    return MP_ADDED;
  } else {
    /* First link in multilink mode */

    mp->local_mrru = lcp->want_mrru;
    mp->peer_mrru = lcp->his_mrru;
    mp->local_is12bit = lcp->want_shortseq;
    mp->peer_is12bit = lcp->his_shortseq;
    mp->peer = dl->peer;

    throughput_destroy(&mp->link.stats.total);
    throughput_init(&mp->link.stats.total, mp->cfg.autoload.period);
    throughput_callback(&mp->link.stats.total, mp_UpDown, mp);
    memset(mp->link.Queue, '\0', sizeof mp->link.Queue);
    memset(mp->link.proto_in, '\0', sizeof mp->link.proto_in);
    memset(mp->link.proto_out, '\0', sizeof mp->link.proto_out);

    /* Tell the link who it belongs to */
    dl->physical->link.stats.parent = &mp->link.stats.total;

    mp->out.seq = 0;
    mp->out.link = 0;
    mp->out.af = AF_INET;
    mp->seq.min_in = 0;
    mp->seq.next_in = 0;

    /*
     * Now we create our server socket.
     * If it already exists, join it.  Otherwise, create and own it
     */
    switch (mpserver_Open(&mp->server, &mp->peer)) {
    case MPSERVER_CONNECTED:
      log_Printf(LogPHASE, "mp: Transfer link on %s\n",
                mp->server.socket.sun_path);
      mp->server.send.dl = dl;		/* Defer 'till it's safe to send */
      return MP_LINKSENT;
    case MPSERVER_FAILED:
      return MP_FAILED;
    case MPSERVER_LISTENING:
      log_Printf(LogPHASE, "mp: Listening on %s\n", mp->server.socket.sun_path);
      log_Printf(LogPHASE, "    First link: %s\n", dl->name);

      /* Re-point our NCP layers at our MP link */
      ncp_SetLink(&mp->bundle->ncp, &mp->link);

      /* Our lcp's already up 'cos of the NULL parent */
      if (ccp_SetOpenMode(&mp->link.ccp)) {
        fsm_Up(&mp->link.ccp.fsm);
        fsm_Open(&mp->link.ccp.fsm);
      }

      mp->active = 1;
      break;
    }
  }

  return MP_UP;
}