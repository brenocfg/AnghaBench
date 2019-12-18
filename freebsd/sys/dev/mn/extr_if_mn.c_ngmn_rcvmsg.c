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
struct schan {unsigned long rx_error; unsigned long short_error; unsigned long crc_error; unsigned long dribble_error; unsigned long long_error; unsigned long abort_error; unsigned long overflow_error; unsigned long tx_pending; int /*<<< orphan*/  prev_error; int /*<<< orphan*/  last_error; scalar_t__ last_xmit; scalar_t__ last_rxerr; scalar_t__ last_recv; int /*<<< orphan*/  hook; } ;
struct TYPE_2__ {scalar_t__ typecookie; scalar_t__ cmd; int arglen; } ;
struct ng_mesg {TYPE_1__ header; scalar_t__ data; } ;
struct mn_softc {unsigned long cnt_fec; unsigned long cnt_cvc; struct schan** ch; int /*<<< orphan*/  falc_irq; int /*<<< orphan*/  falc_state; int /*<<< orphan*/  framer_state; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int M32_CHAN ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 scalar_t__ NGM_GENERIC_COOKIE ; 
 scalar_t__ NGM_TEXT_CONFIG ; 
 scalar_t__ NGM_TEXT_STATUS ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 char* NG_HOOK_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mn_softc* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 scalar_t__ NG_TEXTRESPONSE ; 
 int /*<<< orphan*/  ngmn_config (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 int strlen (char*) ; 
 scalar_t__ time_second ; 

__attribute__((used)) static int
ngmn_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	struct mn_softc *sc;
	struct ng_mesg *resp = NULL;
	struct schan *sch;
	char *s, *r;
	int pos, i;
	struct ng_mesg *msg;

	NGI_GET_MSG(item, msg);
	sc = NG_NODE_PRIVATE(node);

	if (msg->header.typecookie != NGM_GENERIC_COOKIE) {
		NG_FREE_ITEM(item);
		NG_FREE_MSG(msg);
		return (EINVAL);
	}
		
	if (msg->header.cmd != NGM_TEXT_CONFIG && 
	    msg->header.cmd != NGM_TEXT_STATUS) {
		NG_FREE_ITEM(item);
		NG_FREE_MSG(msg);
		return (EINVAL);
	}

	NG_MKRESPONSE(resp, msg, sizeof(struct ng_mesg) + NG_TEXTRESPONSE,
	    M_NOWAIT);
	if (resp == NULL) {
		NG_FREE_ITEM(item);
		NG_FREE_MSG(msg);
		return (ENOMEM);
	}

	if (msg->header.arglen) 
		s = (char *)msg->data;
	else
		s = NULL;
	r = (char *)resp->data;
	*r = '\0';

	if (msg->header.cmd == NGM_TEXT_CONFIG) {
		ngmn_config(node, s, r);
		resp->header.arglen = strlen(r) + 1;
		NG_RESPOND_MSG(i, node, item, resp);
		NG_FREE_MSG(msg);
		return (0);
	}
	pos = 0;
	pos += sprintf(pos + r,"Framer status %b;\n", sc->framer_state, "\20"
	    "\40LOS\37AIS\36LFA\35RRA"
	    "\34AUXP\33NMF\32LMFA\31frs0.0"
	    "\30frs1.7\27TS16RA\26TS16LOS\25TS16AIS"
	    "\24TS16LFA\23frs1.2\22XLS\21XLO"
	    "\20RS1\17rsw.6\16RRA\15RY0"
	    "\14RY1\13RY2\12RY3\11RY4"
	    "\10SI1\7SI2\6rsp.5\5rsp.4"
	    "\4rsp.3\3RSIF\2RS13\1RS15");
	pos += sprintf(pos + r,"    Framing errors: %lu", sc->cnt_fec);
	pos += sprintf(pos + r,"  Code Violations: %lu\n", sc->cnt_cvc);
	
	pos += sprintf(pos + r,"    Falc State %b;\n", sc->falc_state, "\20"
	    "\40LOS\37AIS\36LFA\35RRA"
	    "\34AUXP\33NMF\32LMFA\31frs0.0"
	    "\30frs1.7\27TS16RA\26TS16LOS\25TS16AIS"
	    "\24TS16LFA\23frs1.2\22XLS\21XLO"
	    "\20RS1\17rsw.6\16RRA\15RY0"
	    "\14RY1\13RY2\12RY3\11RY4"
	    "\10SI1\7SI2\6rsp.5\5rsp.4"
	    "\4rsp.3\3RSIF\2RS13\1RS15");
	pos += sprintf(pos + r, "    Falc IRQ %b\n", sc->falc_irq, "\20"
	    "\40RME\37RFS\36T8MS\35RMB\34CASC\33CRC4\32SA6SC\31RPF"
	    "\30b27\27RDO\26ALLS\25XDU\24XMB\23b22\22XLSC\21XPR"
	    "\20FAR\17LFA\16MFAR\15T400MS\14AIS\13LOS\12RAR\11RA"
	    "\10ES\7SEC\6LMFA16\5AIS16\4RA16\3API\2SLN\1SLP");
	for (i = 0; i < M32_CHAN; i++) {
		if (!sc->ch[i])
			continue;
		sch = sc->ch[i];

		pos += sprintf(r + pos, "  Chan %d <%s> ",
		    i, NG_HOOK_NAME(sch->hook));

		pos += sprintf(r + pos, "  Last Rx: ");
		if (sch->last_recv)
			pos += sprintf(r + pos, "%lu s",
			    (unsigned long)(time_second - sch->last_recv));
		else
			pos += sprintf(r + pos, "never");

		pos += sprintf(r + pos, ", last RxErr: ");
		if (sch->last_rxerr)
			pos += sprintf(r + pos, "%lu s",
			    (unsigned long)(time_second - sch->last_rxerr));
		else
			pos += sprintf(r + pos, "never");

		pos += sprintf(r + pos, ", last Tx: ");
		if (sch->last_xmit)
			pos += sprintf(r + pos, "%lu s\n",
			    (unsigned long)(time_second - sch->last_xmit));
		else
			pos += sprintf(r + pos, "never\n");

		pos += sprintf(r + pos, "    RX error(s) %lu", sch->rx_error);
		pos += sprintf(r + pos, " Short: %lu", sch->short_error);
		pos += sprintf(r + pos, " CRC: %lu", sch->crc_error);
		pos += sprintf(r + pos, " Mod8: %lu", sch->dribble_error);
		pos += sprintf(r + pos, " Long: %lu", sch->long_error);
		pos += sprintf(r + pos, " Abort: %lu", sch->abort_error);
		pos += sprintf(r + pos, " Overflow: %lu\n", sch->overflow_error);

		pos += sprintf(r + pos, "    Last error: %b  Prev error: %b\n",
		    sch->last_error, "\20\7SHORT\5CRC\4MOD8\3LONG\2ABORT\1OVERRUN",
		    sch->prev_error, "\20\7SHORT\5CRC\4MOD8\3LONG\2ABORT\1OVERRUN");
		pos += sprintf(r + pos, "    Xmit bytes pending %ld\n",
		    sch->tx_pending);
	}
	resp->header.arglen = pos + 1;

	/* Take care of synchronous response, if any */
	NG_RESPOND_MSG(i, node, item, resp);
	NG_FREE_MSG(msg);
	return (0);
}