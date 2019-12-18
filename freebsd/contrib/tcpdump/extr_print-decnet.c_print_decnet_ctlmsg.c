#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sh_flags; } ;
union routehdr {TYPE_1__ rh_short; } ;
struct TYPE_8__ {int /*<<< orphan*/  eh_data; int /*<<< orphan*/  eh_hello; int /*<<< orphan*/  eh_router; int /*<<< orphan*/  eh_blksize; int /*<<< orphan*/  eh_info; int /*<<< orphan*/  eh_src; int /*<<< orphan*/  eh_ueco; int /*<<< orphan*/  eh_eco; int /*<<< orphan*/  eh_vers; int /*<<< orphan*/  rh_hello; int /*<<< orphan*/  rh_priority; int /*<<< orphan*/  rh_blksize; int /*<<< orphan*/  rh_info; int /*<<< orphan*/  rh_src; int /*<<< orphan*/  rh_ueco; int /*<<< orphan*/  rh_eco; int /*<<< orphan*/  rh_vers; int /*<<< orphan*/  r2_src; int /*<<< orphan*/  r1_src; int /*<<< orphan*/  te_data; int /*<<< orphan*/  te_src; int /*<<< orphan*/  ve_fcnval; int /*<<< orphan*/  ve_src; int /*<<< orphan*/  in_hello; int /*<<< orphan*/  in_ueco; int /*<<< orphan*/  in_eco; int /*<<< orphan*/  in_vers; int /*<<< orphan*/  in_blksize; int /*<<< orphan*/  in_info; int /*<<< orphan*/  in_src; } ;
union controlmsg {TYPE_4__ cm_ehello; TYPE_4__ cm_rhello; TYPE_4__ cm_l2rout; TYPE_4__ cm_l1rou; TYPE_4__ cm_test; TYPE_4__ cm_ver; TYPE_4__ cm_init; } ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct verifmsg {int dummy; } ;
struct testmsg {int dummy; } ;
struct rhellomsg {int dummy; } ;
struct l2rout {int dummy; } ;
struct l1rout {int dummy; } ;
struct initmsg {int dummy; } ;
struct ehellomsg {int dummy; } ;
typedef  int /*<<< orphan*/  srcea ;
typedef  int /*<<< orphan*/  rtea ;
typedef  int /*<<< orphan*/  netdissect_options ;
struct TYPE_6__ {int /*<<< orphan*/  dne_nodeaddr; } ;
struct TYPE_7__ {TYPE_2__ dne_remote; } ;
typedef  TYPE_3__ etheraddr ;

/* Variables and functions */
 int EXTRACT_LE_16BITS (int /*<<< orphan*/ ) ; 
 int EXTRACT_LE_8BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (TYPE_4__) ; 
 int RMF_CTLMASK ; 
#define  RMF_EHELLO 134 
#define  RMF_INIT 133 
#define  RMF_L1ROUT 132 
#define  RMF_L2ROUT 131 
#define  RMF_RHELLO 130 
#define  RMF_TEST 129 
#define  RMF_VER 128 
 int /*<<< orphan*/  dnaddr_string (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int print_elist (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_i_info (int /*<<< orphan*/ *,int) ; 
 int print_l1_routes (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int print_l2_routes (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_t_info (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
print_decnet_ctlmsg(netdissect_options *ndo,
                    register const union routehdr *rhp, u_int length,
                    u_int caplen)
{
	/* Our caller has already checked for mflags */
	int mflags = EXTRACT_LE_8BITS(rhp->rh_short.sh_flags);
	register const union controlmsg *cmp = (const union controlmsg *)rhp;
	int src, dst, info, blksize, eco, ueco, hello, other, vers;
	etheraddr srcea, rtea;
	int priority;
	const char *rhpx = (const char *)rhp;
	int ret;

	switch (mflags & RMF_CTLMASK) {
	case RMF_INIT:
	    ND_PRINT((ndo, "init "));
	    if (length < sizeof(struct initmsg))
		goto trunc;
	    ND_TCHECK(cmp->cm_init);
	    src = EXTRACT_LE_16BITS(cmp->cm_init.in_src);
	    info = EXTRACT_LE_8BITS(cmp->cm_init.in_info);
	    blksize = EXTRACT_LE_16BITS(cmp->cm_init.in_blksize);
	    vers = EXTRACT_LE_8BITS(cmp->cm_init.in_vers);
	    eco = EXTRACT_LE_8BITS(cmp->cm_init.in_eco);
	    ueco = EXTRACT_LE_8BITS(cmp->cm_init.in_ueco);
	    hello = EXTRACT_LE_16BITS(cmp->cm_init.in_hello);
	    print_t_info(ndo, info);
	    ND_PRINT((ndo,
		"src %sblksize %d vers %d eco %d ueco %d hello %d",
			dnaddr_string(ndo, src), blksize, vers, eco, ueco,
			hello));
	    ret = 1;
	    break;
	case RMF_VER:
	    ND_PRINT((ndo, "verification "));
	    if (length < sizeof(struct verifmsg))
		goto trunc;
	    ND_TCHECK(cmp->cm_ver);
	    src = EXTRACT_LE_16BITS(cmp->cm_ver.ve_src);
	    other = EXTRACT_LE_8BITS(cmp->cm_ver.ve_fcnval);
	    ND_PRINT((ndo, "src %s fcnval %o", dnaddr_string(ndo, src), other));
	    ret = 1;
	    break;
	case RMF_TEST:
	    ND_PRINT((ndo, "test "));
	    if (length < sizeof(struct testmsg))
		goto trunc;
	    ND_TCHECK(cmp->cm_test);
	    src = EXTRACT_LE_16BITS(cmp->cm_test.te_src);
	    other = EXTRACT_LE_8BITS(cmp->cm_test.te_data);
	    ND_PRINT((ndo, "src %s data %o", dnaddr_string(ndo, src), other));
	    ret = 1;
	    break;
	case RMF_L1ROUT:
	    ND_PRINT((ndo, "lev-1-routing "));
	    if (length < sizeof(struct l1rout))
		goto trunc;
	    ND_TCHECK(cmp->cm_l1rou);
	    src = EXTRACT_LE_16BITS(cmp->cm_l1rou.r1_src);
	    ND_PRINT((ndo, "src %s ", dnaddr_string(ndo, src)));
	    ret = print_l1_routes(ndo, &(rhpx[sizeof(struct l1rout)]),
				length - sizeof(struct l1rout));
	    break;
	case RMF_L2ROUT:
	    ND_PRINT((ndo, "lev-2-routing "));
	    if (length < sizeof(struct l2rout))
		goto trunc;
	    ND_TCHECK(cmp->cm_l2rout);
	    src = EXTRACT_LE_16BITS(cmp->cm_l2rout.r2_src);
	    ND_PRINT((ndo, "src %s ", dnaddr_string(ndo, src)));
	    ret = print_l2_routes(ndo, &(rhpx[sizeof(struct l2rout)]),
				length - sizeof(struct l2rout));
	    break;
	case RMF_RHELLO:
	    ND_PRINT((ndo, "router-hello "));
	    if (length < sizeof(struct rhellomsg))
		goto trunc;
	    ND_TCHECK(cmp->cm_rhello);
	    vers = EXTRACT_LE_8BITS(cmp->cm_rhello.rh_vers);
	    eco = EXTRACT_LE_8BITS(cmp->cm_rhello.rh_eco);
	    ueco = EXTRACT_LE_8BITS(cmp->cm_rhello.rh_ueco);
	    memcpy((char *)&srcea, (const char *)&(cmp->cm_rhello.rh_src),
		sizeof(srcea));
	    src = EXTRACT_LE_16BITS(srcea.dne_remote.dne_nodeaddr);
	    info = EXTRACT_LE_8BITS(cmp->cm_rhello.rh_info);
	    blksize = EXTRACT_LE_16BITS(cmp->cm_rhello.rh_blksize);
	    priority = EXTRACT_LE_8BITS(cmp->cm_rhello.rh_priority);
	    hello = EXTRACT_LE_16BITS(cmp->cm_rhello.rh_hello);
	    print_i_info(ndo, info);
	    ND_PRINT((ndo,
	    "vers %d eco %d ueco %d src %s blksize %d pri %d hello %d",
			vers, eco, ueco, dnaddr_string(ndo, src),
			blksize, priority, hello));
	    ret = print_elist(&(rhpx[sizeof(struct rhellomsg)]),
				length - sizeof(struct rhellomsg));
	    break;
	case RMF_EHELLO:
	    ND_PRINT((ndo, "endnode-hello "));
	    if (length < sizeof(struct ehellomsg))
		goto trunc;
	    ND_TCHECK(cmp->cm_ehello);
	    vers = EXTRACT_LE_8BITS(cmp->cm_ehello.eh_vers);
	    eco = EXTRACT_LE_8BITS(cmp->cm_ehello.eh_eco);
	    ueco = EXTRACT_LE_8BITS(cmp->cm_ehello.eh_ueco);
	    memcpy((char *)&srcea, (const char *)&(cmp->cm_ehello.eh_src),
		sizeof(srcea));
	    src = EXTRACT_LE_16BITS(srcea.dne_remote.dne_nodeaddr);
	    info = EXTRACT_LE_8BITS(cmp->cm_ehello.eh_info);
	    blksize = EXTRACT_LE_16BITS(cmp->cm_ehello.eh_blksize);
	    /*seed*/
	    memcpy((char *)&rtea, (const char *)&(cmp->cm_ehello.eh_router),
		sizeof(rtea));
	    dst = EXTRACT_LE_16BITS(rtea.dne_remote.dne_nodeaddr);
	    hello = EXTRACT_LE_16BITS(cmp->cm_ehello.eh_hello);
	    other = EXTRACT_LE_8BITS(cmp->cm_ehello.eh_data);
	    print_i_info(ndo, info);
	    ND_PRINT((ndo,
	"vers %d eco %d ueco %d src %s blksize %d rtr %s hello %d data %o",
			vers, eco, ueco, dnaddr_string(ndo, src),
			blksize, dnaddr_string(ndo, dst), hello, other));
	    ret = 1;
	    break;

	default:
	    ND_PRINT((ndo, "unknown control message"));
	    ND_DEFAULTPRINT((const u_char *)rhp, min(length, caplen));
	    ret = 1;
	    break;
	}
	return (ret);

trunc:
	return (0);
}