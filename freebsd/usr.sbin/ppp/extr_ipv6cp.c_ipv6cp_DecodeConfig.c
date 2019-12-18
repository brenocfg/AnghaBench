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
typedef  int /*<<< orphan*/  u_char ;
struct ipv6cp {int peer_tokenreq; int his_reject; int my_reject; int /*<<< orphan*/  myaddr; int /*<<< orphan*/ * my_ifid; int /*<<< orphan*/  fsm; int /*<<< orphan*/ * his_ifid; } ;
struct TYPE_2__ {int id; int len; } ;
struct fsm_opt {TYPE_1__ hdr; int /*<<< orphan*/ * data; } ;
struct fsm_decode {scalar_t__ rejend; scalar_t__ rej; scalar_t__ nakend; scalar_t__ nak; } ;
struct fsm {int /*<<< orphan*/  bundle; } ;

/* Variables and functions */
 int IPV6CP_IFIDLEN ; 
 int /*<<< orphan*/  LogIPV6CP ; 
 int /*<<< orphan*/  LogPHASE ; 
#define  MODE_NAK 131 
 int MODE_NOP ; 
#define  MODE_REJ 130 
#define  MODE_REQ 129 
 int /*<<< orphan*/  SetInterfaceID (int /*<<< orphan*/ *,int) ; 
#define  TY_TOKEN 128 
 int /*<<< orphan*/  bundle_AdjustFilters (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipv6cp* fsm2ipv6cp (struct fsm*) ; 
 int /*<<< orphan*/  fsm_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_opt_normalise (struct fsm_decode*) ; 
 struct fsm_opt* fsm_readopt (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fsm_rej (struct fsm_decode*,struct fsm_opt*) ; 
 int /*<<< orphan*/  ipcp_SetIPv6address (struct ipv6cp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6cp_ValidateInterfaceID (struct ipv6cp*,int /*<<< orphan*/ *,struct fsm_decode*) ; 
 int /*<<< orphan*/  log_IsKept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* protoname (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static void
ipv6cp_DecodeConfig(struct fsm *fp, u_char *cp, u_char *end, int mode_type,
                    struct fsm_decode *dec)
{
  /* Deal with incoming PROTO_IPV6CP */
  struct ipv6cp *ipv6cp = fsm2ipv6cp(fp);
  int n;
  char tbuff[100];
  u_char ifid[IPV6CP_IFIDLEN], zero[IPV6CP_IFIDLEN];
  struct fsm_opt *opt;

  memset(zero, 0, IPV6CP_IFIDLEN);

  while (end - cp >= (int)sizeof(opt->hdr)) {
    if ((opt = fsm_readopt(&cp)) == NULL)
      break;

    snprintf(tbuff, sizeof tbuff, " %s[%d]", protoname(opt->hdr.id),
             opt->hdr.len);

    switch (opt->hdr.id) {
    case TY_TOKEN:
      memcpy(ifid, opt->data, IPV6CP_IFIDLEN);
      log_Printf(LogIPV6CP, "%s 0x%02x%02x%02x%02x%02x%02x%02x%02x\n", tbuff,
		 ifid[0], ifid[1], ifid[2], ifid[3], ifid[4], ifid[5], ifid[6], ifid[7]);

      switch (mode_type) {
      case MODE_REQ:
        ipv6cp->peer_tokenreq = 1;
        ipv6cp_ValidateInterfaceID(ipv6cp, ifid, dec);
        break;

      case MODE_NAK:
        if (memcmp(ifid, zero, IPV6CP_IFIDLEN) == 0) {
          log_Printf(log_IsKept(LogIPV6CP) ? LogIPV6CP : LogPHASE,
		     "0x0000000000000000: Unacceptable IntefaceID!\n");
          fsm_Close(&ipv6cp->fsm);
        } else if (memcmp(ifid, ipv6cp->his_ifid, IPV6CP_IFIDLEN) == 0) {
          log_Printf(log_IsKept(LogIPV6CP) ? LogIPV6CP : LogPHASE,
		     "0x%02x%02x%02x%02x%02x%02x%02x%02x: "
		     "Unacceptable IntefaceID!\n",
		     ifid[0], ifid[1], ifid[2], ifid[3],
		     ifid[4], ifid[5], ifid[6], ifid[7]);
        } else if (memcmp(ifid, ipv6cp->my_ifid, IPV6CP_IFIDLEN) != 0) {
          n = 100;
	  while (n && !ipcp_SetIPv6address(ipv6cp, ifid, ipv6cp->his_ifid)) {
	    do {
	      n--;
	      SetInterfaceID(ifid, 1);
	    } while (n && memcmp(ifid, ipv6cp->his_ifid, IPV6CP_IFIDLEN) == 0);
	  }

          if (n == 0) {
            log_Printf(log_IsKept(LogIPV6CP) ? LogIPV6CP : LogPHASE,
                       "0x0000000000000000: Unacceptable IntefaceID!\n");
            fsm_Close(&ipv6cp->fsm);
          } else {
	    log_Printf(LogIPV6CP, "%s changing IntefaceID: "
		       "0x%02x%02x%02x%02x%02x%02x%02x%02x "
		       "--> 0x%02x%02x%02x%02x%02x%02x%02x%02x\n", tbuff,
		       ipv6cp->my_ifid[0], ipv6cp->my_ifid[1],
		       ipv6cp->my_ifid[2], ipv6cp->my_ifid[3],
		       ipv6cp->my_ifid[4], ipv6cp->my_ifid[5],
		       ipv6cp->my_ifid[6], ipv6cp->my_ifid[7],
		       ifid[0], ifid[1], ifid[2], ifid[3],
		       ifid[4], ifid[5], ifid[6], ifid[7]);
            memcpy(ipv6cp->my_ifid, ifid, IPV6CP_IFIDLEN);
            bundle_AdjustFilters(fp->bundle, &ipv6cp->myaddr, NULL);
          }
        }
        break;

      case MODE_REJ:
        ipv6cp->his_reject |= (1 << opt->hdr.id);
        break;
      }
      break;

    default:
      if (mode_type != MODE_NOP) {
        ipv6cp->my_reject |= (1 << opt->hdr.id);
        fsm_rej(dec, opt);
      }
      break;
    }
  }

  if (mode_type != MODE_NOP) {
    if (mode_type == MODE_REQ && !ipv6cp->peer_tokenreq) {
      if (dec->rejend == dec->rej && dec->nakend == dec->nak) {
        /*
         * Pretend the peer has requested a TOKEN.
         * We do this to ensure that we only send one NAK if the only
         * reason for the NAK is because the peer isn't sending a
         * TY_TOKEN REQ.  This stops us from repeatedly trying to tell
         * the peer that we have to have an IP address on their end.
         */
        ipv6cp->peer_tokenreq = 1;
      }
      memset(ifid, 0, IPV6CP_IFIDLEN);
      ipv6cp_ValidateInterfaceID(ipv6cp, ifid, dec);
    }
    fsm_opt_normalise(dec);
  }
}