#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_6__ {int success; struct TYPE_6__* next; } ;
typedef  TYPE_1__ rpcbs_rmtcalllist ;
struct TYPE_7__ {int success; struct TYPE_7__* next; } ;
typedef  TYPE_2__ rpcbs_addrlist ;
typedef  TYPE_3__* rpcb_stat_byvers ;
struct TYPE_8__ {int setinfo; int unsetinfo; int* info; TYPE_1__* rmtinfo; TYPE_2__* addrinfo; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ CLNT_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct timeval) ; 
 int MAX (int,int) ; 
 int MAXFIELD ; 
 int MAXLINE ; 
#define  PMAPPROC_CALLIT 135 
#define  PMAPPROC_GETPORT 134 
#define  PMAPPROC_SET 133 
#define  PMAPPROC_UNSET 132 
 int /*<<< orphan*/  PMAPPROG ; 
#define  RPCBPROC_CALLIT 131 
#define  RPCBPROC_GETADDR 130 
 size_t RPCBPROC_GETADDRLIST ; 
 int /*<<< orphan*/  RPCBPROC_GETSTAT ; 
 size_t RPCBPROC_INDIRECT ; 
#define  RPCBPROC_SET 129 
#define  RPCBPROC_UNSET 128 
 int /*<<< orphan*/  RPCBVERS4 ; 
 size_t RPCBVERS_2_STAT ; 
 size_t RPCBVERS_3_STAT ; 
 size_t RPCBVERS_4_STAT ; 
 scalar_t__ RPC_SUCCESS ; 
 int TABSTOP ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clnt_pcreateerror (char*) ; 
 int /*<<< orphan*/  clnt_perror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * clnt_rpcbind_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * local_rpcb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_getaddrstat (size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  print_rmtcallstat (size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rpcb_highproc_2 ; 
 int rpcb_highproc_3 ; 
 int rpcb_highproc_4 ; 
 int /*<<< orphan*/  spaces (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int strlen (char const*) ; 
 scalar_t__ xdr_rpcb_stat_byvers ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
rpcbgetstat(int argc, char **argv)
{
	rpcb_stat_byvers inf;
	struct timeval minutetimeout;
	register CLIENT *client;
	char *host;
	int i, j;
	rpcbs_addrlist *pa;
	rpcbs_rmtcalllist *pr;
	int cnt, flen;
#define	MAXFIELD	64
	char fieldbuf[MAXFIELD];
#define	MAXLINE		256
	char linebuf[MAXLINE];
	char *cp, *lp;
	const char *pmaphdr[] = {
		"NULL", "SET", "UNSET", "GETPORT",
		"DUMP", "CALLIT"
	};
	const char *rpcb3hdr[] = {
		"NULL", "SET", "UNSET", "GETADDR", "DUMP", "CALLIT", "TIME",
		"U2T", "T2U"
	};
	const char *rpcb4hdr[] = {
		"NULL", "SET", "UNSET", "GETADDR", "DUMP", "CALLIT", "TIME",
		"U2T",  "T2U", "VERADDR", "INDRECT", "GETLIST", "GETSTAT"
	};

#define	TABSTOP	8

	if (argc >= 1) {
		host = argv[0];
		client = clnt_rpcbind_create(host, RPCBVERS4, NULL);
	} else
		client = local_rpcb(PMAPPROG, RPCBVERS4);
	if (client == (CLIENT *)NULL) {
		clnt_pcreateerror("rpcinfo: can't contact rpcbind");
		exit(1);
	}
	minutetimeout.tv_sec = 60;
	minutetimeout.tv_usec = 0;
	memset((char *)&inf, 0, sizeof (rpcb_stat_byvers));
	if (CLNT_CALL(client, RPCBPROC_GETSTAT, (xdrproc_t) xdr_void, NULL,
		(xdrproc_t) xdr_rpcb_stat_byvers, (char *)&inf, minutetimeout)
			!= RPC_SUCCESS) {
		clnt_perror(client, "rpcinfo: can't contact rpcbind: ");
		exit(1);
	}
	printf("PORTMAP (version 2) statistics\n");
	lp = linebuf;
	for (i = 0; i <= rpcb_highproc_2; i++) {
		fieldbuf[0] = '\0';
		switch (i) {
		case PMAPPROC_SET:
			sprintf(fieldbuf, "%d/", inf[RPCBVERS_2_STAT].setinfo);
			break;
		case PMAPPROC_UNSET:
			sprintf(fieldbuf, "%d/",
				inf[RPCBVERS_2_STAT].unsetinfo);
			break;
		case PMAPPROC_GETPORT:
			cnt = 0;
			for (pa = inf[RPCBVERS_2_STAT].addrinfo; pa;
				pa = pa->next)
				cnt += pa->success;
			sprintf(fieldbuf, "%d/", cnt);
			break;
		case PMAPPROC_CALLIT:
			cnt = 0;
			for (pr = inf[RPCBVERS_2_STAT].rmtinfo; pr;
				pr = pr->next)
				cnt += pr->success;
			sprintf(fieldbuf, "%d/", cnt);
			break;
		default: break;  /* For the remaining ones */
		}
		cp = &fieldbuf[0] + strlen(fieldbuf);
		sprintf(cp, "%d", inf[RPCBVERS_2_STAT].info[i]);
		flen = strlen(fieldbuf);
		printf("%s%s", pmaphdr[i],
			spaces((TABSTOP * (1 + flen / TABSTOP))
			- strlen(pmaphdr[i])));
		sprintf(lp, "%s%s", fieldbuf,
			spaces(cnt = ((TABSTOP * (1 + flen / TABSTOP))
			- flen)));
		lp += (flen + cnt);
	}
	printf("\n%s\n\n", linebuf);

	if (inf[RPCBVERS_2_STAT].info[PMAPPROC_CALLIT]) {
		printf("PMAP_RMTCALL call statistics\n");
		print_rmtcallstat(RPCBVERS_2_STAT, &inf[RPCBVERS_2_STAT]);
		printf("\n");
	}

	if (inf[RPCBVERS_2_STAT].info[PMAPPROC_GETPORT]) {
		printf("PMAP_GETPORT call statistics\n");
		print_getaddrstat(RPCBVERS_2_STAT, &inf[RPCBVERS_2_STAT]);
		printf("\n");
	}

	printf("RPCBIND (version 3) statistics\n");
	lp = linebuf;
	for (i = 0; i <= rpcb_highproc_3; i++) {
		fieldbuf[0] = '\0';
		switch (i) {
		case RPCBPROC_SET:
			sprintf(fieldbuf, "%d/", inf[RPCBVERS_3_STAT].setinfo);
			break;
		case RPCBPROC_UNSET:
			sprintf(fieldbuf, "%d/",
				inf[RPCBVERS_3_STAT].unsetinfo);
			break;
		case RPCBPROC_GETADDR:
			cnt = 0;
			for (pa = inf[RPCBVERS_3_STAT].addrinfo; pa;
				pa = pa->next)
				cnt += pa->success;
			sprintf(fieldbuf, "%d/", cnt);
			break;
		case RPCBPROC_CALLIT:
			cnt = 0;
			for (pr = inf[RPCBVERS_3_STAT].rmtinfo; pr;
				pr = pr->next)
				cnt += pr->success;
			sprintf(fieldbuf, "%d/", cnt);
			break;
		default: break;  /* For the remaining ones */
		}
		cp = &fieldbuf[0] + strlen(fieldbuf);
		sprintf(cp, "%d", inf[RPCBVERS_3_STAT].info[i]);
		flen = strlen(fieldbuf);
		printf("%s%s", rpcb3hdr[i],
			spaces((TABSTOP * (1 + flen / TABSTOP))
			- strlen(rpcb3hdr[i])));
		sprintf(lp, "%s%s", fieldbuf,
			spaces(cnt = ((TABSTOP * (1 + flen / TABSTOP))
			- flen)));
		lp += (flen + cnt);
	}
	printf("\n%s\n\n", linebuf);

	if (inf[RPCBVERS_3_STAT].info[RPCBPROC_CALLIT]) {
		printf("RPCB_RMTCALL (version 3) call statistics\n");
		print_rmtcallstat(RPCBVERS_3_STAT, &inf[RPCBVERS_3_STAT]);
		printf("\n");
	}

	if (inf[RPCBVERS_3_STAT].info[RPCBPROC_GETADDR]) {
		printf("RPCB_GETADDR (version 3) call statistics\n");
		print_getaddrstat(RPCBVERS_3_STAT, &inf[RPCBVERS_3_STAT]);
		printf("\n");
	}

	printf("RPCBIND (version 4) statistics\n");

	for (j = 0; j <= 9; j += 9) { /* Just two iterations for printing */
		lp = linebuf;
		for (i = j; i <= MAX(8, rpcb_highproc_4 - 9 + j); i++) {
			fieldbuf[0] = '\0';
			switch (i) {
			case RPCBPROC_SET:
				sprintf(fieldbuf, "%d/",
					inf[RPCBVERS_4_STAT].setinfo);
				break;
			case RPCBPROC_UNSET:
				sprintf(fieldbuf, "%d/",
					inf[RPCBVERS_4_STAT].unsetinfo);
				break;
			case RPCBPROC_GETADDR:
				cnt = 0;
				for (pa = inf[RPCBVERS_4_STAT].addrinfo; pa;
					pa = pa->next)
					cnt += pa->success;
				sprintf(fieldbuf, "%d/", cnt);
				break;
			case RPCBPROC_CALLIT:
				cnt = 0;
				for (pr = inf[RPCBVERS_4_STAT].rmtinfo; pr;
					pr = pr->next)
					cnt += pr->success;
				sprintf(fieldbuf, "%d/", cnt);
				break;
			default: break;  /* For the remaining ones */
			}
			cp = &fieldbuf[0] + strlen(fieldbuf);
			/*
			 * XXX: We also add RPCBPROC_GETADDRLIST queries to
			 * RPCB_GETADDR because rpcbind includes the
			 * RPCB_GETADDRLIST successes in RPCB_GETADDR.
			 */
			if (i != RPCBPROC_GETADDR)
			    sprintf(cp, "%d", inf[RPCBVERS_4_STAT].info[i]);
			else
			    sprintf(cp, "%d", inf[RPCBVERS_4_STAT].info[i] +
			    inf[RPCBVERS_4_STAT].info[RPCBPROC_GETADDRLIST]);
			flen = strlen(fieldbuf);
			printf("%s%s", rpcb4hdr[i],
				spaces((TABSTOP * (1 + flen / TABSTOP))
				- strlen(rpcb4hdr[i])));
			sprintf(lp, "%s%s", fieldbuf,
				spaces(cnt = ((TABSTOP * (1 + flen / TABSTOP))
				- flen)));
			lp += (flen + cnt);
		}
		printf("\n%s\n", linebuf);
	}

	if (inf[RPCBVERS_4_STAT].info[RPCBPROC_CALLIT] ||
			    inf[RPCBVERS_4_STAT].info[RPCBPROC_INDIRECT]) {
		printf("\n");
		printf("RPCB_RMTCALL (version 4) call statistics\n");
		print_rmtcallstat(RPCBVERS_4_STAT, &inf[RPCBVERS_4_STAT]);
	}

	if (inf[RPCBVERS_4_STAT].info[RPCBPROC_GETADDR]) {
		printf("\n");
		printf("RPCB_GETADDR (version 4) call statistics\n");
		print_getaddrstat(RPCBVERS_4_STAT, &inf[RPCBVERS_4_STAT]);
	}
	clnt_destroy(client);
}