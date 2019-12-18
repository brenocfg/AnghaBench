#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_7__ {int link; int /*<<< orphan*/  af; } ;
struct TYPE_5__ {size_t his_mru; } ;
struct link {TYPE_1__ lcp; } ;
struct mp {size_t peer_mrru; TYPE_3__ out; struct link link; } ;
struct mbuf {scalar_t__ m_len; } ;
struct datalink {scalar_t__ state; struct datalink* next; TYPE_2__* physical; } ;
struct TYPE_8__ {struct mp mp; } ;
struct bundle {struct datalink* links; TYPE_4__ ncp; } ;
struct TYPE_6__ {struct link link; scalar_t__ out; } ;

/* Variables and functions */
 scalar_t__ DATALINK_OPEN ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MB_MPOUT ; 
 struct mbuf* link_Dequeue (struct link*) ; 
 size_t link_QueueLen (struct link*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 struct mbuf* m_get (size_t,int /*<<< orphan*/ ) ; 
 size_t m_length (struct mbuf*) ; 
 int /*<<< orphan*/  m_settype (struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* mbuf_Read (struct mbuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mp_Output (struct mp*,struct bundle*,struct link*,struct mbuf*,int,int) ; 
 int /*<<< orphan*/  mp_QueueLen (struct mp*) ; 
 int /*<<< orphan*/  ncp_PushPacket (TYPE_4__*,int /*<<< orphan*/ *,struct link*) ; 

int
mp_FillPhysicalQueues(struct bundle *bundle)
{
  struct mp *mp = &bundle->ncp.mp;
  struct datalink *dl, *fdl;
  size_t total, add, len;
  int thislink, nlinks, nopenlinks, sendasip;
  u_int32_t begin, end;
  struct mbuf *m, *mo;
  struct link *bestlink;

  thislink = nlinks = nopenlinks = 0;
  for (fdl = NULL, dl = bundle->links; dl; dl = dl->next) {
    /* Include non-open links here as mp->out.link will stay more correct */
    if (!fdl) {
      if (thislink == mp->out.link)
        fdl = dl;
      else
        thislink++;
    }
    nlinks++;
    if (dl->state == DATALINK_OPEN)
      nopenlinks++;
  }

  if (!fdl) {
    fdl = bundle->links;
    if (!fdl)
      return 0;
    thislink = 0;
  }

  total = 0;
  for (dl = fdl; nlinks > 0; dl = dl->next, nlinks--, thislink++) {
    if (!dl) {
      dl = bundle->links;
      thislink = 0;
    }

    if (dl->state != DATALINK_OPEN)
      continue;

    if (dl->physical->out)
      /* this link has suffered a short write.  Let it continue */
      continue;

    add = link_QueueLen(&dl->physical->link);
    if (add) {
      /* this link has got stuff already queued.  Let it continue */
      total += add;
      continue;
    }

    if (!mp_QueueLen(mp)) {
      int mrutoosmall;

      /*
       * If there's only a single open link in our bundle and we haven't got
       * MP level link compression, queue outbound traffic directly via that
       * link's protocol stack rather than using the MP link.  This results
       * in the outbound traffic going out as PROTO_IP or PROTO_IPV6 rather
       * than PROTO_MP.
       */

      mrutoosmall = 0;
      sendasip = nopenlinks < 2;
      if (sendasip) {
        if (dl->physical->link.lcp.his_mru < mp->peer_mrru) {
          /*
           * Actually, forget it.  This test is done against the MRRU rather
           * than the packet size so that we don't end up sending some data
           * in MP fragments and some data in PROTO_IP packets.  That's just
           * too likely to upset some ppp implementations.
           */
          mrutoosmall = 1;
          sendasip = 0;
        }
      }

      bestlink = sendasip ? &dl->physical->link : &mp->link;
      if (!ncp_PushPacket(&bundle->ncp, &mp->out.af, bestlink))
        break;	/* Nothing else to send */

      if (mrutoosmall)
        log_Printf(LogDEBUG, "Don't send data as PROTO_IP, MRU < MRRU\n");
      else if (sendasip)
        log_Printf(LogDEBUG, "Sending data as PROTO_IP, not PROTO_MP\n");

      if (sendasip) {
        add = link_QueueLen(&dl->physical->link);
        if (add) {
          /* this link has got stuff already queued.  Let it continue */
          total += add;
          continue;
        }
      }
    }

    m = link_Dequeue(&mp->link);
    if (m) {
      len = m_length(m);
      begin = 1;
      end = 0;

      while (!end) {
        if (dl->state == DATALINK_OPEN) {
          /* Write at most his_mru bytes to the physical link */
          if (len <= dl->physical->link.lcp.his_mru) {
            mo = m;
            end = 1;
            m_settype(mo, MB_MPOUT);
          } else {
            /* It's > his_mru, chop the packet (`m') into bits */
            mo = m_get(dl->physical->link.lcp.his_mru, MB_MPOUT);
            len -= mo->m_len;
            m = mbuf_Read(m, MBUF_CTOP(mo), mo->m_len);
          }
          mp_Output(mp, bundle, &dl->physical->link, mo, begin, end);
          begin = 0;
        }

        if (!end) {
          nlinks--;
          dl = dl->next;
          if (!dl) {
            dl = bundle->links;
            thislink = 0;
          } else
            thislink++;
        }
      }
    }
  }
  mp->out.link = thislink;		/* Start here next time */

  return total;
}