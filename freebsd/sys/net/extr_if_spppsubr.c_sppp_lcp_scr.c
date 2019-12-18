#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
struct TYPE_4__ {int proto; } ;
struct TYPE_3__ {int opts; int magic; int mru; } ;
struct sppp {scalar_t__* confid; scalar_t__* pp_seq; TYPE_2__ hisauth; TYPE_1__ lcp; } ;

/* Variables and functions */
 char CHAP_MD5 ; 
 int /*<<< orphan*/  CONF_REQ ; 
 size_t IDX_LCP ; 
 int LCP_OPT_AUTH_PROTO ; 
 int LCP_OPT_MAGIC ; 
 int LCP_OPT_MRU ; 
 int PPP_CHAP ; 
 int /*<<< orphan*/  PPP_LCP ; 
 int random () ; 
 int /*<<< orphan*/  sppp_cp_send (struct sppp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,char**) ; 

__attribute__((used)) static void
sppp_lcp_scr(struct sppp *sp)
{
	char opt[6 /* magicnum */ + 4 /* mru */ + 5 /* chap */];
	int i = 0;
	u_short authproto;

	if (sp->lcp.opts & (1 << LCP_OPT_MAGIC)) {
		if (! sp->lcp.magic)
			sp->lcp.magic = random();
		opt[i++] = LCP_OPT_MAGIC;
		opt[i++] = 6;
		opt[i++] = sp->lcp.magic >> 24;
		opt[i++] = sp->lcp.magic >> 16;
		opt[i++] = sp->lcp.magic >> 8;
		opt[i++] = sp->lcp.magic;
	}

	if (sp->lcp.opts & (1 << LCP_OPT_MRU)) {
		opt[i++] = LCP_OPT_MRU;
		opt[i++] = 4;
		opt[i++] = sp->lcp.mru >> 8;
		opt[i++] = sp->lcp.mru;
	}

	if (sp->lcp.opts & (1 << LCP_OPT_AUTH_PROTO)) {
		authproto = sp->hisauth.proto;
		opt[i++] = LCP_OPT_AUTH_PROTO;
		opt[i++] = authproto == PPP_CHAP? 5: 4;
		opt[i++] = authproto >> 8;
		opt[i++] = authproto;
		if (authproto == PPP_CHAP)
			opt[i++] = CHAP_MD5;
	}

	sp->confid[IDX_LCP] = ++sp->pp_seq[IDX_LCP];
	sppp_cp_send (sp, PPP_LCP, CONF_REQ, sp->confid[IDX_LCP], i, &opt);
}