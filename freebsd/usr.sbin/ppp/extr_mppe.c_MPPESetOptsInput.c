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
typedef  int u_int32_t ;
struct fsm_opt {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {scalar_t__ state; scalar_t__ keybits; } ;
struct ccp_config {TYPE_1__ mppe; } ;
struct bundle {int dummy; } ;

/* Variables and functions */
 int MODE_ACK ; 
 int MODE_NAK ; 
 int MPPE_ConfigVal (struct bundle*,struct ccp_config const*) ; 
 int /*<<< orphan*/  MPPE_MasterKeyValid ; 
#define  MPPE_OPT_128BIT 130 
#define  MPPE_OPT_40BIT 129 
#define  MPPE_OPT_56BIT 128 
 int MPPE_OPT_BITMASK ; 
 int MPPE_OPT_MASK ; 
 int MPPE_OPT_STATELESS ; 
 scalar_t__ MPPE_STATEFUL ; 
 scalar_t__ MPPE_STATELESS ; 
 int /*<<< orphan*/  ua_htonl (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ua_ntohl (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
MPPESetOptsInput(struct bundle *bundle, struct fsm_opt *o,
                 const struct ccp_config *cfg)
{
  u_int32_t mval, peer;
  int res = MODE_ACK;

  ua_ntohl(o->data, &peer);
  if (!MPPE_MasterKeyValid) {
    if (peer != 0) {
      peer = 0;
      ua_htonl(&peer, o->data);
      return MODE_NAK;
    } else
      return MODE_ACK;
  }

  mval = MPPE_ConfigVal(bundle, cfg);

  if (peer & ~MPPE_OPT_MASK)
    /* He's asking for bits we don't know about */
    res = MODE_NAK;

  if (peer & MPPE_OPT_STATELESS) {
    if (cfg->mppe.state == MPPE_STATEFUL)
      /* Peer can't have stateless */
      res = MODE_NAK;
    else
      /* Peer wants stateless, that's ok */
      mval |= MPPE_OPT_STATELESS;
  } else {
    if (cfg->mppe.state == MPPE_STATELESS)
      /* Peer must have stateless */
      res = MODE_NAK;
    else
      /* Peer doesn't want stateless, that's ok */
      mval &= ~MPPE_OPT_STATELESS;
  }

  /* If we've got a configured number of keybits - the peer must use that */
  if (cfg->mppe.keybits) {
    ua_htonl(&mval, o->data);
    return peer == mval ? res : MODE_NAK;
  }

  /* If a specific number of bits hasn't been requested, we'll need to NAK */
  switch (peer & MPPE_OPT_BITMASK) {
  case MPPE_OPT_128BIT:
  case MPPE_OPT_56BIT:
  case MPPE_OPT_40BIT:
    break;
  default:
    res = MODE_NAK;
  }

  /* Suggest the best number of bits */
  mval &= ~MPPE_OPT_BITMASK;
  if (peer & MPPE_OPT_128BIT)
    mval |= MPPE_OPT_128BIT;
  else if (peer & MPPE_OPT_56BIT)
    mval |= MPPE_OPT_56BIT;
  else if (peer & MPPE_OPT_40BIT)
    mval |= MPPE_OPT_40BIT;
  else
    mval |= MPPE_OPT_128BIT;
  ua_htonl(&mval, o->data);

  return res;
}