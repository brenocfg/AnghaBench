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
typedef  int u_short ;
struct mppe_state {int cohnum; int flushrequired; int /*<<< orphan*/  rc4key; int /*<<< orphan*/  sesskey; int /*<<< orphan*/  keylen; scalar_t__ stateless; } ;
struct mbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  reqid; } ;
struct ccp {int compin; int uncompin; TYPE_1__ fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_RESETREQ ; 
 int /*<<< orphan*/  LogCCP ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogERROR ; 
 char* MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MB_CCPOUT ; 
 int /*<<< orphan*/  MPPEKeyChange (struct mppe_state*) ; 
 int MPPE_ENCRYPTED ; 
 int MPPE_FLUSHED ; 
 int MPPE_HEADER_BITMASK ; 
 int MPPE_HEADER_FLAG ; 
 int MPPE_HEADER_FLAGMASK ; 
 int MPPE_HEADER_FLAGSHIFT ; 
 scalar_t__ MPPE_HEADER_STATEFUL_KEYCHANGES ; 
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,int,char*,char*) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_Output (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_DumpBp (int /*<<< orphan*/ ,char*,struct mbuf*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int m_length (struct mbuf*) ; 
 struct mbuf* mbuf_Read (struct mbuf*,int*,int) ; 
 int ntohs (int) ; 

__attribute__((used)) static struct mbuf *
MPPEInput(void *v, struct ccp *ccp, u_short *proto, struct mbuf *mp)
{
  struct mppe_state *mip = (struct mppe_state *)v;
  u_short prefix;
  char *rp;
  int dictinit, flushed, ilen, len, n;

  ilen = m_length(mp);
  dictinit = 0;
  ccp->compin += ilen;

  log_Printf(LogDEBUG, "MPPE: Input: Proto %02x (%d bytes)\n", *proto, ilen);
  log_DumpBp(LogDEBUG, "MPPE: Input: Packet:", mp);

  mp = mbuf_Read(mp, &prefix, 2);
  prefix = ntohs(prefix);
  flushed = prefix & MPPE_FLUSHED;
  prefix &= ~flushed;
  if ((prefix & MPPE_HEADER_BITMASK) != MPPE_ENCRYPTED) {
    log_Printf(LogERROR, "MPPE: Input: Invalid packet (flags = 0x%x)\n",
               (prefix & MPPE_HEADER_BITMASK) | flushed);
    m_freem(mp);
    return NULL;
  }

  prefix &= ~MPPE_HEADER_BITMASK;

  if (!flushed && mip->stateless) {
    log_Printf(LogCCP, "MPPEInput: Packet without MPPE_FLUSHED set"
               " in stateless mode\n");
    flushed = MPPE_FLUSHED;
    /* Should we really continue ? */
  }

  if (mip->stateless) {
    /* Change our key for each missed packet in stateless mode */
    while (prefix != mip->cohnum) {
      log_Printf(LogDEBUG, "MPPEInput: Key changed [%u]\n", prefix);
      MPPEKeyChange(mip);
      /*
       * mip->cohnum contains what we received last time in stateless
       * mode.
       */
      mip->cohnum++;
      mip->cohnum &= ~MPPE_HEADER_BITMASK;
    }
    dictinit = 1;
  } else {
    if (flushed) {
      /*
       * We can always process a flushed packet.
       * Catch up on any outstanding key changes.
       */
      n = (prefix >> MPPE_HEADER_FLAGSHIFT) -
          (mip->cohnum >> MPPE_HEADER_FLAGSHIFT);
      if (n < 0)
        n += MPPE_HEADER_STATEFUL_KEYCHANGES;
      while (n--) {
        log_Printf(LogDEBUG, "MPPEInput: Key changed during catchup [%u]\n",
                   prefix);
        MPPEKeyChange(mip);
      }
      mip->flushrequired = 0;
      mip->cohnum = prefix;
      dictinit = 1;
    }

    if (mip->flushrequired) {
      /*
       * Perhaps we should be lenient if
       * (prefix & MPPE_HEADER_FLAGMASK) == MPPE_HEADER_FLAG
       * The spec says that we shouldn't be though....
       */
      log_Printf(LogDEBUG, "MPPE: Not flushed - discarded\n");
      fsm_Output(&ccp->fsm, CODE_RESETREQ, ccp->fsm.reqid++, NULL, 0,
                 MB_CCPOUT);
      m_freem(mp);
      return NULL;
    }

    if (prefix != mip->cohnum) {
      /*
       * We're in stateful mode and didn't receive the expected
       * packet.  Send a reset request, but don't tell the CCP layer
       * about it as we don't expect to receive a Reset ACK !
       * Guess what... M$ invented this !
       */
      log_Printf(LogCCP, "MPPE: Input: Got seq %u, not %u\n",
                 prefix, mip->cohnum);
      fsm_Output(&ccp->fsm, CODE_RESETREQ, ccp->fsm.reqid++, NULL, 0,
                 MB_CCPOUT);
      mip->flushrequired = 1;
      m_freem(mp);
      return NULL;
    }

    if ((prefix & MPPE_HEADER_FLAGMASK) == MPPE_HEADER_FLAG) {
      log_Printf(LogDEBUG, "MPPEInput: Key changed [%u]\n", prefix);
      MPPEKeyChange(mip);
      dictinit = 1;
    } else if (flushed)
      dictinit = 1;

    /*
     * mip->cohnum contains what we expect to receive next time in stateful
     * mode.
     */
    mip->cohnum++;
    mip->cohnum &= ~MPPE_HEADER_BITMASK;
  }

  if (dictinit) {
    log_Printf(LogDEBUG, "MPPEInput: Dictionary initialised [%u]\n", prefix);
    RC4_set_key(&mip->rc4key, mip->keylen, mip->sesskey);
  }

  mp = mbuf_Read(mp, proto, 2);
  RC4(&mip->rc4key, 2, (char *)proto, (char *)proto);
  *proto = ntohs(*proto);

  rp = MBUF_CTOP(mp);
  len = m_length(mp);
  RC4(&mip->rc4key, len, rp, rp);

  log_Printf(LogDEBUG, "MPPEInput: Decrypted: Proto %02x (%d bytes)\n",
             *proto, len);
  log_DumpBp(LogDEBUG, "MPPEInput: Decrypted: Packet:", mp);

  ccp->uncompin += len;

  return mp;
}