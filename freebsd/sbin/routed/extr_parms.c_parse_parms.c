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
struct tgate {int intnet_metric; void* intnet_addr; void* intnet_mask; int r1net_mask; void* r1net_net; void* r1net_match; char* parm_name; int parm_int_state; int parm_rdisc_pref; int parm_rdisc_int; int parm_d_metric; int parm_adj_inmetric; int parm_adj_outmetric; struct tgate* tgate_next; TYPE_1__* tgate_nets; void* tgate_addr; void* parm_mask; void* parm_net; struct tgate* r1net_next; struct tgate* intnet_next; } ;
struct r1net {int intnet_metric; void* intnet_addr; void* intnet_mask; int r1net_mask; void* r1net_net; void* r1net_match; char* parm_name; int parm_int_state; int parm_rdisc_pref; int parm_rdisc_int; int parm_d_metric; int parm_adj_inmetric; int parm_adj_outmetric; struct r1net* tgate_next; TYPE_1__* tgate_nets; void* tgate_addr; void* parm_mask; void* parm_net; struct r1net* r1net_next; struct r1net* intnet_next; } ;
struct parm {int intnet_metric; void* intnet_addr; void* intnet_mask; int r1net_mask; void* r1net_net; void* r1net_match; char* parm_name; int parm_int_state; int parm_rdisc_pref; int parm_rdisc_int; int parm_d_metric; int parm_adj_inmetric; int parm_adj_outmetric; struct parm* tgate_next; TYPE_1__* tgate_nets; void* tgate_addr; void* parm_mask; void* parm_net; struct parm* r1net_next; struct parm* intnet_next; } ;
struct intnet {int intnet_metric; void* intnet_addr; void* intnet_mask; int r1net_mask; void* r1net_net; void* r1net_match; char* parm_name; int parm_int_state; int parm_rdisc_pref; int parm_rdisc_int; int parm_d_metric; int parm_adj_inmetric; int parm_adj_outmetric; struct intnet* tgate_next; TYPE_1__* tgate_nets; void* tgate_addr; void* parm_mask; void* parm_net; struct intnet* r1net_next; struct intnet* intnet_next; } ;
typedef  int /*<<< orphan*/  parm ;
typedef  void* naddr ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {void* net; void* mask; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  CKF (int,int) ; 
 int GROUP_IS_ADV_OUT ; 
 int GROUP_IS_SOL_OUT ; 
 int HOPCNT_INFINITY ; 
 int HOST_MASK ; 
 scalar_t__ IF_NAME_LEN ; 
 int IS_ADV_OUT ; 
 int IS_BCAST_RDISC ; 
 int IS_DISTRUST ; 
 int IS_NO_ADV_OUT ; 
 int IS_NO_AG ; 
 int IS_NO_RDISC ; 
 int IS_NO_RIP ; 
 int IS_NO_RIPV1_IN ; 
 int IS_NO_RIPV1_OUT ; 
 int IS_NO_RIPV2_IN ; 
 int IS_NO_RIPV2_OUT ; 
 int IS_NO_RIP_MCAST ; 
 int IS_NO_RIP_OUT ; 
 int IS_NO_SOL_OUT ; 
 int IS_NO_SUPER_AG ; 
 int IS_PASSIVE ; 
 int IS_PM_RDISC ; 
 int IS_REDIRECT_OK ; 
 scalar_t__ IS_RIP_OUT_OFF (int) ; 
 int IS_SOL_OUT ; 
 int MAX_TGATE_NETS ; 
 int MaxMaxAdvertiseInterval ; 
 int MinMaxAdvertiseInterval ; 
 scalar_t__ PARS (char*) ; 
 scalar_t__ PARSEQ (char*) ; 
 int /*<<< orphan*/  RIP_AUTH_MD5 ; 
 int /*<<< orphan*/  RIP_AUTH_PW ; 
 scalar_t__ RIP_DEFAULT ; 
 char const* bad_str (char const*) ; 
 char const* check_parms (struct tgate*) ; 
 int /*<<< orphan*/  free (struct tgate*) ; 
 char* get_passwd (char*,char*,struct tgate*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gethost (char*,void**) ; 
 int /*<<< orphan*/  getnet (char*,void**,void**) ; 
 scalar_t__ htonl (scalar_t__) ; 
 struct tgate* intnets ; 
 int /*<<< orphan*/  memset (struct tgate*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_quote (char**,char*,char*,char*,int) ; 
 struct tgate* r1nets ; 
 scalar_t__ rtmalloc (int,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strcspn (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 int strspn (char*,char*) ; 
 scalar_t__ strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 struct tgate* tgates ; 

const char *					/* 0 or error message */
parse_parms(char *line,
	    int safe)			/* 1=from secure file */
{
#define PARS(str) (!strcasecmp(tgt, str))
#define PARSEQ(str) (!strncasecmp(tgt, str"=", sizeof(str)))
#define CKF(g,b) {if (0 != (parm.parm_int_state & ((g) & ~(b)))) break;	\
	parm.parm_int_state |= (b);}
	struct parm parm;
	struct intnet *intnetp;
	struct r1net *r1netp;
	struct tgate *tg;
	naddr addr, mask;
	char delim, *val0 = NULL, *tgt, *val, *p;
	const char *msg;
	char buf[BUFSIZ], buf2[BUFSIZ];
	int i;


	/* "subnet=x.y.z.u/mask[,metric]" must be alone on the line */
	if (!strncasecmp(line, "subnet=", sizeof("subnet=")-1)
	    && *(val = &line[sizeof("subnet=")-1]) != '\0') {
		if (0 > parse_quote(&val, ",", &delim, buf, sizeof(buf)))
			return bad_str(line);
		intnetp = (struct intnet*)rtmalloc(sizeof(*intnetp),
						   "parse_parms subnet");
		intnetp->intnet_metric = 1;
		if (delim == ',') {
			intnetp->intnet_metric = (int)strtol(val+1,&p,0);
			if (*p != '\0'
			    || intnetp->intnet_metric <= 0
			    || intnetp->intnet_metric >= HOPCNT_INFINITY) {
				free(intnetp);
				return bad_str(line);
			}
		}
		if (!getnet(buf, &intnetp->intnet_addr, &intnetp->intnet_mask)
		    || intnetp->intnet_mask == HOST_MASK
		    || intnetp->intnet_addr == RIP_DEFAULT) {
			free(intnetp);
			return bad_str(line);
		}
		intnetp->intnet_addr = htonl(intnetp->intnet_addr);
		intnetp->intnet_next = intnets;
		intnets = intnetp;
		return 0;
	}

	/* "ripv1_mask=x.y.z.u/mask1,mask2" must be alone on the line.
	 * This requires that x.y.z.u/mask1 be considered a subnet of
	 * x.y.z.u/mask2, as if x.y.z.u/mask2 were a class-full network.
	 */
	if (!strncasecmp(line, "ripv1_mask=", sizeof("ripv1_mask=")-1)
	    && *(val = &line[sizeof("ripv1_mask=")-1]) != '\0') {
		if (0 > parse_quote(&val, ",", &delim, buf, sizeof(buf))
		    || delim == '\0')
			return bad_str(line);
		if ((i = (int)strtol(val+1, &p, 0)) <= 0
		    || i > 32 || *p != '\0')
			return bad_str(line);
		r1netp = (struct r1net *)rtmalloc(sizeof(*r1netp),
						  "parse_parms ripv1_mask");
		r1netp->r1net_mask = HOST_MASK << (32-i);
		if (!getnet(buf, &r1netp->r1net_net, &r1netp->r1net_match)
		    || r1netp->r1net_net == RIP_DEFAULT
		    || r1netp->r1net_mask > r1netp->r1net_match) {
			free(r1netp);
			return bad_str(line);
		}
		r1netp->r1net_next = r1nets;
		r1nets = r1netp;
		return 0;
	}

	memset(&parm, 0, sizeof(parm));

	for (;;) {
		tgt = line + strspn(line, " ,\n\r");
		if (*tgt == '\0' || *tgt == '#')
			break;
		line = tgt+strcspn(tgt, "= #,\n\r");
		delim = *line;
		if (delim == '=') {
			val0 = ++line;
			if (0 > parse_quote(&line, " #,\n\r",&delim,
					    buf,sizeof(buf)))
				return bad_str(tgt);
		} else {
			val0 = NULL;
		}
		if (delim != '\0') {
			for (;;) {
				*line = '\0';
				if (delim == '#')
					break;
				++line;
				if (delim != ' '
				    || (delim = *line) != ' ')
					break;
			}
		}

		if (PARSEQ("if")) {
			if (parm.parm_name[0] != '\0'
			    || strlen(buf) > IF_NAME_LEN)
				return bad_str(tgt);
			strcpy(parm.parm_name, buf);

		} else if (PARSEQ("addr")) {
			/* This is a bad idea, because the address based
			 * sets of parameters cannot be checked for
			 * consistency with the interface name parameters.
			 * The parm_net stuff is needed to allow several
			 * -F settings.
			 */
			if (val0 == NULL || !getnet(val0, &addr, &mask)
			    || parm.parm_name[0] != '\0')
				return bad_str(tgt);
			parm.parm_net = addr;
			parm.parm_mask = mask;
			parm.parm_name[0] = '\n';

		} else if (PARSEQ("passwd")) {
			/* since cleartext passwords are so weak allow
			 * them anywhere
			 */
			if (val0 == NULL)
				return bad_str("no passwd");
			msg = get_passwd(tgt,val0,&parm,RIP_AUTH_PW,1);
			if (msg) {
				*val0 = '\0';
				return bad_str(msg);
			}

		} else if (PARSEQ("md5_passwd")) {
			msg = get_passwd(tgt,val0,&parm,RIP_AUTH_MD5,safe);
			if (msg) {
				*val0 = '\0';
				return bad_str(msg);
			}

		} else if (PARS("no_ag")) {
			parm.parm_int_state |= (IS_NO_AG | IS_NO_SUPER_AG);

		} else if (PARS("no_super_ag")) {
			parm.parm_int_state |= IS_NO_SUPER_AG;

		} else if (PARS("no_rip_out")) {
			parm.parm_int_state |= IS_NO_RIP_OUT;

		} else if (PARS("no_ripv1_in")) {
			parm.parm_int_state |= IS_NO_RIPV1_IN;

		} else if (PARS("no_ripv2_in")) {
			parm.parm_int_state |= IS_NO_RIPV2_IN;

		} else if (PARS("ripv2_out")) {
			if (parm.parm_int_state & IS_NO_RIPV2_OUT)
				return bad_str(tgt);
			parm.parm_int_state |= IS_NO_RIPV1_OUT;

		} else if (PARS("ripv2")) {
			if ((parm.parm_int_state & IS_NO_RIPV2_OUT)
			    || (parm.parm_int_state & IS_NO_RIPV2_IN))
				return bad_str(tgt);
			parm.parm_int_state |= (IS_NO_RIPV1_IN
						| IS_NO_RIPV1_OUT);

		} else if (PARS("no_rip")) {
			CKF(IS_PM_RDISC, IS_NO_RIP);

		} else if (PARS("no_rip_mcast")) {
			parm.parm_int_state |= IS_NO_RIP_MCAST;

		} else if (PARS("no_rdisc")) {
			CKF((GROUP_IS_SOL_OUT|GROUP_IS_ADV_OUT), IS_NO_RDISC);

		} else if (PARS("no_solicit")) {
			CKF(GROUP_IS_SOL_OUT, IS_NO_SOL_OUT);

		} else if (PARS("send_solicit")) {
			CKF(GROUP_IS_SOL_OUT, IS_SOL_OUT);

		} else if (PARS("no_rdisc_adv")) {
			CKF(GROUP_IS_ADV_OUT, IS_NO_ADV_OUT);

		} else if (PARS("rdisc_adv")) {
			CKF(GROUP_IS_ADV_OUT, IS_ADV_OUT);

		} else if (PARS("bcast_rdisc")) {
			parm.parm_int_state |= IS_BCAST_RDISC;

		} else if (PARS("passive")) {
			CKF((GROUP_IS_SOL_OUT|GROUP_IS_ADV_OUT), IS_NO_RDISC);
			parm.parm_int_state |= IS_NO_RIP | IS_PASSIVE;

		} else if (PARSEQ("rdisc_pref")) {
			if (parm.parm_rdisc_pref != 0
			    || (parm.parm_rdisc_pref = (int)strtol(buf,&p,0),
				*p != '\0'))
				return bad_str(tgt);

		} else if (PARS("pm_rdisc")) {
			if (IS_RIP_OUT_OFF(parm.parm_int_state))
				return bad_str(tgt);
			parm.parm_int_state |= IS_PM_RDISC;

		} else if (PARSEQ("rdisc_interval")) {
			if (parm.parm_rdisc_int != 0
			    || (parm.parm_rdisc_int = (int)strtoul(buf,&p,0),
				*p != '\0')
			    || parm.parm_rdisc_int < MinMaxAdvertiseInterval
			    || parm.parm_rdisc_int > MaxMaxAdvertiseInterval)
				return bad_str(tgt);

		} else if (PARSEQ("fake_default")) {
			if (parm.parm_d_metric != 0
			    || IS_RIP_OUT_OFF(parm.parm_int_state)
			    || (i = strtoul(buf,&p,0), *p != '\0')
			    || i > HOPCNT_INFINITY-1)
				return bad_str(tgt);
			parm.parm_d_metric = i;

		} else if (PARSEQ("adj_inmetric")) {
			if (parm.parm_adj_inmetric != 0
			    || (i = strtoul(buf,&p,0), *p != '\0')
			    || i > HOPCNT_INFINITY-1)
				return bad_str(tgt);
			parm.parm_adj_inmetric = i;

		} else if (PARSEQ("adj_outmetric")) {
			if (parm.parm_adj_outmetric != 0
			    || (i = strtoul(buf,&p,0), *p != '\0')
			    || i > HOPCNT_INFINITY-1)
				return bad_str(tgt);
			parm.parm_adj_outmetric = i;

		} else if (PARSEQ("trust_gateway")) {
			/* look for trust_gateway=x.y.z|net/mask|...) */
			p = buf;
			if (0 > parse_quote(&p, "|", &delim,
					    buf2, sizeof(buf2))
			    || !gethost(buf2,&addr))
				return bad_str(tgt);
			tg = (struct tgate *)rtmalloc(sizeof(*tg),
						      "parse_parms"
						      "trust_gateway");
			memset(tg, 0, sizeof(*tg));
			tg->tgate_addr = addr;
			i = 0;
			/* The default is to trust all routes. */
			while (delim == '|') {
				p++;
				if (i >= MAX_TGATE_NETS
				    || 0 > parse_quote(&p, "|", &delim,
						       buf2, sizeof(buf2))
				    || !getnet(buf2, &tg->tgate_nets[i].net,
					       &tg->tgate_nets[i].mask)
				    || tg->tgate_nets[i].net == RIP_DEFAULT
				    || tg->tgate_nets[i].mask == 0) {
					free(tg);
					return bad_str(tgt);
				}
				i++;
			}
			tg->tgate_next = tgates;
			tgates = tg;
			parm.parm_int_state |= IS_DISTRUST;

		} else if (PARS("redirect_ok")) {
			parm.parm_int_state |= IS_REDIRECT_OK;

		} else {
			return bad_str(tgt);	/* error */
		}
	}

	return check_parms(&parm);
#undef PARS
#undef PARSEQ
}