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
struct protoent {char* p_name; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct nat44_cfg_spool {int port; TYPE_1__ addr; } ;
struct nat44_cfg_redir {int mode; int spool_cnt; int lport; int pport_cnt; int pport; int rport; int rport_cnt; TYPE_1__ raddr; TYPE_1__ paddr; TYPE_1__ laddr; int /*<<< orphan*/  proto; } ;
struct nat44_cfg_nat {char* name; char* if_name; int mode; int redir_cnt; TYPE_1__ ip; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int PKT_ALIAS_DENY_INCOMING ; 
 int PKT_ALIAS_LOG ; 
 int PKT_ALIAS_PROXY_ONLY ; 
 int PKT_ALIAS_RESET_ON_ADDR_CHANGE ; 
 int PKT_ALIAS_REVERSE ; 
 int PKT_ALIAS_SAME_PORTS ; 
 int PKT_ALIAS_SKIP_GLOBAL ; 
 int PKT_ALIAS_UNREGISTERED_ONLY ; 
#define  REDIR_ADDR 130 
#define  REDIR_PORT 129 
#define  REDIR_PROTO 128 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 struct protoent* getprotobynumber (int /*<<< orphan*/ ) ; 
 char* inet_ntoa (TYPE_1__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
nat_show_cfg(struct nat44_cfg_nat *n, void *arg)
{
	int i, cnt, off;
	struct nat44_cfg_redir *t;
	struct nat44_cfg_spool *s;
	caddr_t buf;
	struct protoent *p;

	buf = (caddr_t)n;
	off = sizeof(*n);
	printf("ipfw nat %s config", n->name);
	if (strlen(n->if_name) != 0)
		printf(" if %s", n->if_name);
	else if (n->ip.s_addr != 0)
		printf(" ip %s", inet_ntoa(n->ip));
	while (n->mode != 0) {
		if (n->mode & PKT_ALIAS_LOG) {
			printf(" log");
			n->mode &= ~PKT_ALIAS_LOG;
		} else if (n->mode & PKT_ALIAS_DENY_INCOMING) {
			printf(" deny_in");
			n->mode &= ~PKT_ALIAS_DENY_INCOMING;
		} else if (n->mode & PKT_ALIAS_SAME_PORTS) {
			printf(" same_ports");
			n->mode &= ~PKT_ALIAS_SAME_PORTS;
		} else if (n->mode & PKT_ALIAS_SKIP_GLOBAL) {
			printf(" skip_global");
			n->mode &= ~PKT_ALIAS_SKIP_GLOBAL;
		} else if (n->mode & PKT_ALIAS_UNREGISTERED_ONLY) {
			printf(" unreg_only");
			n->mode &= ~PKT_ALIAS_UNREGISTERED_ONLY;
		} else if (n->mode & PKT_ALIAS_RESET_ON_ADDR_CHANGE) {
			printf(" reset");
			n->mode &= ~PKT_ALIAS_RESET_ON_ADDR_CHANGE;
		} else if (n->mode & PKT_ALIAS_REVERSE) {
			printf(" reverse");
			n->mode &= ~PKT_ALIAS_REVERSE;
		} else if (n->mode & PKT_ALIAS_PROXY_ONLY) {
			printf(" proxy_only");
			n->mode &= ~PKT_ALIAS_PROXY_ONLY;
		}
	}
	/* Print all the redirect's data configuration. */
	for (cnt = 0; cnt < n->redir_cnt; cnt++) {
		t = (struct nat44_cfg_redir *)&buf[off];
		off += sizeof(struct nat44_cfg_redir);
		switch (t->mode) {
		case REDIR_ADDR:
			printf(" redirect_addr");
			if (t->spool_cnt == 0)
				printf(" %s", inet_ntoa(t->laddr));
			else
				for (i = 0; i < t->spool_cnt; i++) {
					s = (struct nat44_cfg_spool *)&buf[off];
					if (i)
						printf(",");
					else
						printf(" ");
					printf("%s", inet_ntoa(s->addr));
					off += sizeof(struct nat44_cfg_spool);
				}
			printf(" %s", inet_ntoa(t->paddr));
			break;
		case REDIR_PORT:
			p = getprotobynumber(t->proto);
			printf(" redirect_port %s ", p->p_name);
			if (!t->spool_cnt) {
				printf("%s:%u", inet_ntoa(t->laddr), t->lport);
				if (t->pport_cnt > 1)
					printf("-%u", t->lport +
					    t->pport_cnt - 1);
			} else
				for (i=0; i < t->spool_cnt; i++) {
					s = (struct nat44_cfg_spool *)&buf[off];
					if (i)
						printf(",");
					printf("%s:%u", inet_ntoa(s->addr),
					    s->port);
					off += sizeof(struct nat44_cfg_spool);
				}

			printf(" ");
			if (t->paddr.s_addr)
				printf("%s:", inet_ntoa(t->paddr));
			printf("%u", t->pport);
			if (!t->spool_cnt && t->pport_cnt > 1)
				printf("-%u", t->pport + t->pport_cnt - 1);

			if (t->raddr.s_addr) {
				printf(" %s", inet_ntoa(t->raddr));
				if (t->rport) {
					printf(":%u", t->rport);
					if (!t->spool_cnt && t->rport_cnt > 1)
						printf("-%u", t->rport +
						    t->rport_cnt - 1);
				}
			}
			break;
		case REDIR_PROTO:
			p = getprotobynumber(t->proto);
			printf(" redirect_proto %s %s", p->p_name,
			    inet_ntoa(t->laddr));
			if (t->paddr.s_addr != 0) {
				printf(" %s", inet_ntoa(t->paddr));
				if (t->raddr.s_addr)
					printf(" %s", inet_ntoa(t->raddr));
			}
			break;
		default:
			errx(EX_DATAERR, "unknown redir mode");
			break;
		}
	}
	printf("\n");
}