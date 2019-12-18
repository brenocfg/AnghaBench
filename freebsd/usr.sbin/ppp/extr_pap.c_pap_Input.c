#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_char ;
struct TYPE_12__ {int /*<<< orphan*/  auth_ineed; int /*<<< orphan*/  auth_iwait; } ;
struct TYPE_13__ {TYPE_4__ lcp; } ;
struct physical {TYPE_7__* dl; TYPE_5__ link; } ;
struct mbuf {int dummy; } ;
struct link {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/ * file; } ;
struct TYPE_14__ {TYPE_2__ cfg; } ;
struct bundle {TYPE_6__ radius; } ;
struct TYPE_9__ {int code; scalar_t__ id; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {char* name; TYPE_1__ hdr; } ;
struct authinfo {scalar_t__ id; TYPE_3__ in; } ;
struct TYPE_15__ {struct authinfo pap; } ;

/* Variables and functions */
 scalar_t__ Enabled (struct bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  LogWARN ; 
 int MAXPAPCODE ; 
 char* MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MB_PAPIN ; 
 int /*<<< orphan*/  OPT_IDCHECK ; 
#define  PAP_ACK 130 
#define  PAP_NAK 129 
#define  PAP_REQUEST 128 
 scalar_t__ PHASE_AUTHENTICATE ; 
 scalar_t__ PHASE_NETWORK ; 
 int /*<<< orphan*/  PROTO_PAP ; 
 struct mbuf* auth_ReadHeader (struct authinfo*,struct mbuf*) ; 
 struct mbuf* auth_ReadName (struct authinfo*,struct mbuf*,size_t) ; 
 int /*<<< orphan*/  auth_StopTimer (struct authinfo*) ; 
 int /*<<< orphan*/  auth_Validate (struct bundle*,size_t*,size_t*) ; 
 scalar_t__ bundle_Phase (struct bundle*) ; 
 int /*<<< orphan*/  datalink_AuthNotOk (TYPE_7__*) ; 
 int /*<<< orphan*/  datalink_AuthOk (TYPE_7__*) ; 
 int /*<<< orphan*/  free (size_t*) ; 
 struct physical* link2physical (struct link*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 size_t m_length (struct mbuf*) ; 
 struct mbuf* m_pullup (struct mbuf*) ; 
 int /*<<< orphan*/  m_settype (struct mbuf*,int /*<<< orphan*/ ) ; 
 size_t* malloc (int /*<<< orphan*/ ) ; 
 struct mbuf* mbuf_Read (struct mbuf*,size_t*,size_t) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pap_Failure (struct authinfo*) ; 
 int /*<<< orphan*/  pap_Success (struct authinfo*) ; 
 int /*<<< orphan*/ * papcodes ; 
 int /*<<< orphan*/  radius_Authenticate (TYPE_6__*,struct authinfo*,size_t*,size_t*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlen (size_t*) ; 

struct mbuf *
pap_Input(struct bundle *bundle, struct link *l, struct mbuf *bp)
{
  struct physical *p = link2physical(l);
  struct authinfo *authp = &p->dl->pap;
  u_char nlen, klen, *key;
  const char *txt;
  int txtlen;

  if (p == NULL) {
    log_Printf(LogERROR, "pap_Input: Not a physical link - dropped\n");
    m_freem(bp);
    return NULL;
  }

  if (bundle_Phase(bundle) != PHASE_NETWORK &&
      bundle_Phase(bundle) != PHASE_AUTHENTICATE) {
    log_Printf(LogPHASE, "Unexpected pap input - dropped !\n");
    m_freem(bp);
    return NULL;
  }

  if ((bp = auth_ReadHeader(authp, bp)) == NULL &&
      ntohs(authp->in.hdr.length) == 0) {
    log_Printf(LogWARN, "Pap Input: Truncated header !\n");
    return NULL;
  }

  if (authp->in.hdr.code == 0 || authp->in.hdr.code > MAXPAPCODE) {
    log_Printf(LogPHASE, "Pap Input: %d: Bad PAP code !\n", authp->in.hdr.code);
    m_freem(bp);
    return NULL;
  }

  if (authp->in.hdr.code != PAP_REQUEST && authp->id != authp->in.hdr.id &&
      Enabled(bundle, OPT_IDCHECK)) {
    /* Wrong conversation dude ! */
    log_Printf(LogPHASE, "Pap Input: %s dropped (got id %d, not %d)\n",
               papcodes[authp->in.hdr.code], authp->in.hdr.id, authp->id);
    m_freem(bp);
    return NULL;
  }
  m_settype(bp, MB_PAPIN);
  authp->id = authp->in.hdr.id;		/* We respond with this id */

  if (bp) {
    bp = mbuf_Read(bp, &nlen, 1);
    if (authp->in.hdr.code == PAP_ACK) {
      /*
       * Don't restrict the length of our acknowledgement freetext to
       * nlen (a one-byte length).  Show the rest of the ack packet
       * instead.  This isn't really part of the protocol.....
       */
      bp = m_pullup(bp);
      txt = MBUF_CTOP(bp);
      txtlen = m_length(bp);
    } else {
      bp = auth_ReadName(authp, bp, nlen);
      txt = authp->in.name;
      txtlen = strlen(authp->in.name);
    }
  } else {
    txt = "";
    txtlen = 0;
  }

  log_Printf(LogPHASE, "Pap Input: %s (%.*s)\n",
             papcodes[authp->in.hdr.code], txtlen, txt);

  switch (authp->in.hdr.code) {
    case PAP_REQUEST:
      if (bp == NULL) {
        log_Printf(LogPHASE, "Pap Input: No key given !\n");
        break;
      }
      bp = mbuf_Read(bp, &klen, 1);
      if (m_length(bp) < klen) {
        log_Printf(LogERROR, "Pap Input: Truncated key !\n");
        break;
      }
      if ((key = malloc(klen+1)) == NULL) {
        log_Printf(LogERROR, "Pap Input: Out of memory !\n");
        break;
      }
      bp = mbuf_Read(bp, key, klen);
      key[klen] = '\0';

#ifndef NORADIUS
      if (*bundle->radius.cfg.file) {
        if (!radius_Authenticate(&bundle->radius, authp, authp->in.name,
                                 key, strlen(key), NULL, 0))
          pap_Failure(authp);
      } else
#endif
      if (auth_Validate(bundle, authp->in.name, key))
        pap_Success(authp);
      else
        pap_Failure(authp);

      free(key);
      break;

    case PAP_ACK:
      auth_StopTimer(authp);
      if (p->link.lcp.auth_iwait == PROTO_PAP) {
        p->link.lcp.auth_iwait = 0;
        if (p->link.lcp.auth_ineed == 0)
          /*
           * We've succeeded in our ``login''
           * If we're not expecting  the peer to authenticate (or he already
           * has), proceed to network phase.
           */
          datalink_AuthOk(p->dl);
      }
      break;

    case PAP_NAK:
      auth_StopTimer(authp);
      datalink_AuthNotOk(p->dl);
      break;
  }

  m_freem(bp);
  return NULL;
}