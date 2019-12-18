#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
struct TYPE_3__ {void* s_addr; } ;
struct nat44_cfg_spool {void* port; TYPE_1__ addr; } ;
struct nat44_cfg_redir {scalar_t__ proto; int pport_cnt; int rport_cnt; int /*<<< orphan*/  spool_cnt; void* pport; void* rport; TYPE_1__ raddr; void* lport; TYPE_1__ paddr; TYPE_1__ laddr; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  port_range ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 void* GETLOPORT (int /*<<< orphan*/ ) ; 
 int GETNUMPORTS (int /*<<< orphan*/ ) ; 
 void* INADDR_ANY ; 
 void* INADDR_NONE ; 
 scalar_t__ IPPROTO_SCTP ; 
 int /*<<< orphan*/  REDIR_PORT ; 
 int /*<<< orphan*/  SETLOPORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETNUMPORTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StrToAddr (char*,TYPE_1__*) ; 
 scalar_t__ StrToAddrAndPortRange (char*,TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ StrToPortRange (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ StrToProto (char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int
setup_redir_port(char *buf, int *ac, char ***av)
{
	struct nat44_cfg_redir *r;
	char *sep, *protoName, *lsnat = NULL;
	size_t space;
	u_short numLocalPorts;
	port_range portRange;

	numLocalPorts = 0;

	r = (struct nat44_cfg_redir *)buf;
	r->mode = REDIR_PORT;
	/* Skip nat44_cfg_redir at beginning of buf. */
	buf = &buf[sizeof(struct nat44_cfg_redir)];
	space = sizeof(struct nat44_cfg_redir);

	/*
	 * Extract protocol.
	 */
	r->proto = StrToProto(**av);
	protoName = **av;
	(*av)++; (*ac)--;

	/*
	 * Extract local address.
	 */
	if (strchr(**av, ',') != NULL) {
		r->laddr.s_addr = INADDR_NONE;
		r->lport = ~0;
		numLocalPorts = 1;
		lsnat = **av;
	} else {
		/*
		 * The sctp nat does not allow the port numbers to be mapped to
		 * new port numbers. Therefore, no ports are to be specified
		 * in the target port field.
		 */
		if (r->proto == IPPROTO_SCTP) {
			if (strchr(**av, ':'))
				errx(EX_DATAERR, "redirect_port:"
				    "port numbers do not change in sctp, so do "
				    "not specify them as part of the target");
			else
				StrToAddr(**av, &r->laddr);
		} else {
			if (StrToAddrAndPortRange(**av, &r->laddr, protoName,
			    &portRange) != 0)
				errx(EX_DATAERR, "redirect_port: "
				    "invalid local port range");

			r->lport = GETLOPORT(portRange);
			numLocalPorts = GETNUMPORTS(portRange);
		}
	}
	(*av)++; (*ac)--;

	/*
	 * Extract public port and optionally address.
	 */
	if (strchr(**av, ':') != NULL) {
		if (StrToAddrAndPortRange(**av, &r->paddr, protoName,
		    &portRange) != 0)
			errx(EX_DATAERR, "redirect_port: "
			    "invalid public port range");
	} else {
		r->paddr.s_addr = INADDR_ANY;
		if (StrToPortRange(**av, protoName, &portRange) != 0)
			errx(EX_DATAERR, "redirect_port: "
			    "invalid public port range");
	}

	r->pport = GETLOPORT(portRange);
	if (r->proto == IPPROTO_SCTP) { /* so the logic below still works */
		numLocalPorts = GETNUMPORTS(portRange);
		r->lport = r->pport;
	}
	r->pport_cnt = GETNUMPORTS(portRange);
	(*av)++; (*ac)--;

	/*
	 * Extract remote address and optionally port.
	 */
	/*
	 * NB: isdigit(**av) => we've to check that next parameter is really an
	 * option for this redirect entry, else stop here processing arg[cv].
	 */
	if (*ac != 0 && isdigit(***av)) {
		if (strchr(**av, ':') != NULL) {
			if (StrToAddrAndPortRange(**av, &r->raddr, protoName,
			    &portRange) != 0)
				errx(EX_DATAERR, "redirect_port: "
				    "invalid remote port range");
		} else {
			SETLOPORT(portRange, 0);
			SETNUMPORTS(portRange, 1);
			StrToAddr(**av, &r->raddr);
		}
		(*av)++; (*ac)--;
	} else {
		SETLOPORT(portRange, 0);
		SETNUMPORTS(portRange, 1);
		r->raddr.s_addr = INADDR_ANY;
	}
	r->rport = GETLOPORT(portRange);
	r->rport_cnt = GETNUMPORTS(portRange);

	/*
	 * Make sure port ranges match up, then add the redirect ports.
	 */
	if (numLocalPorts != r->pport_cnt)
		errx(EX_DATAERR, "redirect_port: "
		    "port ranges must be equal in size");

	/* Remote port range is allowed to be '0' which means all ports. */
	if (r->rport_cnt != numLocalPorts &&
	    (r->rport_cnt != 1 || r->rport != 0))
		errx(EX_DATAERR, "redirect_port: remote port must"
		    "be 0 or equal to local port range in size");

	/* Setup LSNAT server pool. */
	if (lsnat != NULL) {
		struct nat44_cfg_spool *spool;

		sep = strtok(lsnat, ",");
		while (sep != NULL) {
			spool = (struct nat44_cfg_spool *)buf;
			space += sizeof(struct nat44_cfg_spool);
			/*
			 * The sctp nat does not allow the port numbers to
			 * be mapped to new port numbers. Therefore, no ports
			 * are to be specified in the target port field.
			 */
			if (r->proto == IPPROTO_SCTP) {
				if (strchr (sep, ':')) {
					errx(EX_DATAERR, "redirect_port:"
					    "port numbers do not change in "
					    "sctp, so do not specify them as "
					    "part of the target");
				} else {
					StrToAddr(sep, &spool->addr);
					spool->port = r->pport;
				}
			} else {
				if (StrToAddrAndPortRange(sep, &spool->addr,
					protoName, &portRange) != 0)
					errx(EX_DATAERR, "redirect_port:"
					    "invalid local port range");
				if (GETNUMPORTS(portRange) != 1)
					errx(EX_DATAERR, "redirect_port: "
					    "local port must be single in "
					    "this context");
				spool->port = GETLOPORT(portRange);
			}
			r->spool_cnt++;
			/* Point to the next possible nat44_cfg_spool. */
			buf = &buf[sizeof(struct nat44_cfg_spool)];
			sep = strtok(NULL, ",");
		}
	}

	return (space);
}