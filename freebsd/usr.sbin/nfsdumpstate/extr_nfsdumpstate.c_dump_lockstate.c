#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nfsd_dumplocklist {int ndllck_size; char* ndllck_fname; void* ndllck_list; } ;
typedef  int /*<<< orphan*/  nbuf ;
struct TYPE_9__ {int nclid_idlen; int* nclid_id; } ;
struct TYPE_8__ {int nclid_idlen; int* nclid_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_6__ {int seqid; int* other; } ;
struct TYPE_10__ {int ndlck_flags; int ndlck_addrfam; TYPE_4__ ndlck_clid; TYPE_3__ ndlck_owner; TYPE_2__ ndlck_cbaddr; int /*<<< orphan*/  ndlck_end; int /*<<< orphan*/  ndlck_first; TYPE_1__ ndlck_stateid; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int DUMPSIZE ; 
 int INET6_ADDRSTRLEN ; 
 int NFSLCK_DELEGREAD ; 
 int NFSLCK_DELEGWRITE ; 
 int NFSLCK_OPEN ; 
 int /*<<< orphan*/  NFSSVC_DUMPLOCKS ; 
 char* deleg_flags (int) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inet_ntop (int const,int /*<<< orphan*/ *,char*,int) ; 
 char* lock_flags (int) ; 
 TYPE_5__* lp ; 
 scalar_t__ nfssvc (int /*<<< orphan*/ ,struct nfsd_dumplocklist*) ; 
 char* open_flags (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_lockstate(char *fname)
{
	struct nfsd_dumplocklist dumplocklist;
	int cnt, i;
#ifdef INET6
	char nbuf[INET6_ADDRSTRLEN];
#endif

	dumplocklist.ndllck_size = DUMPSIZE;
	dumplocklist.ndllck_list = (void *)lp;
	dumplocklist.ndllck_fname = fname;
	if (nfssvc(NFSSVC_DUMPLOCKS, &dumplocklist) < 0)
		errx(1, "Can't dump locks for %s\n", fname);

	printf("%-11s %-36s %-45s %s\n",
	    "Open/Lock",
	    "          Stateid or Lock Range",
	    "Clientaddr",
	    "Owner and ClientID");
	/*
	 * Loop through results, printing them out.
	 */
	cnt = 0;
	while (lp[cnt].ndlck_clid.nclid_idlen > 0 && cnt < DUMPSIZE) {
		if (lp[cnt].ndlck_flags & NFSLCK_OPEN)
			printf("%-11s %9d %08x %08x %08x ",
			    open_flags(lp[cnt].ndlck_flags),
			    lp[cnt].ndlck_stateid.seqid,
			    lp[cnt].ndlck_stateid.other[0],
			    lp[cnt].ndlck_stateid.other[1],
			    lp[cnt].ndlck_stateid.other[2]);
		else if (lp[cnt].ndlck_flags & (NFSLCK_DELEGREAD |
		    NFSLCK_DELEGWRITE))
			printf("%-11s %9d %08x %08x %08x ",
			    deleg_flags(lp[cnt].ndlck_flags),
			    lp[cnt].ndlck_stateid.seqid,
			    lp[cnt].ndlck_stateid.other[0],
			    lp[cnt].ndlck_stateid.other[1],
			    lp[cnt].ndlck_stateid.other[2]);
		else
			printf("%-11s  %17jd %17jd ",
			    lock_flags(lp[cnt].ndlck_flags),
			    lp[cnt].ndlck_first,
			    lp[cnt].ndlck_end);
		switch (lp[cnt].ndlck_addrfam) {
#ifdef INET
		case AF_INET:
			printf("%-45s ",
			    inet_ntoa(lp[cnt].ndlck_cbaddr.sin_addr));
			break;
#endif
#ifdef INET6
		case AF_INET6:
			if (inet_ntop(AF_INET6, &lp[cnt].ndlck_cbaddr.sin6_addr,
			    nbuf, sizeof(nbuf)) != NULL)
				printf("%-45s ", nbuf);
			else
				printf("%-45s ", " ");
			break;
#endif
		default:
			printf("%-45s ", "  ");
			break;
		}
		for (i = 0; i < lp[cnt].ndlck_owner.nclid_idlen; i++)
			printf("%02x", lp[cnt].ndlck_owner.nclid_id[i]);
		printf(" ");
		for (i = 0; i < lp[cnt].ndlck_clid.nclid_idlen; i++)
			printf("%02x", lp[cnt].ndlck_clid.nclid_id[i]);
		printf("\n");
		cnt++;
	}
}