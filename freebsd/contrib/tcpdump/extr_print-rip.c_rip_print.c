#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct rip_netinfo {int dummy; } ;
struct rip {int rip_vers; int /*<<< orphan*/  rip_cmd; } ;
struct TYPE_7__ {int ndo_vflag; int /*<<< orphan*/  const* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
#define  RIPCMD_POLL 133 
#define  RIPCMD_POLLENTRY 132 
#define  RIPCMD_REQUEST 131 
#define  RIPCMD_RESPONSE 130 
#define  RIPCMD_TRACEOFF 129 
#define  RIPCMD_TRACEON 128 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  rip_cmd_values ; 
 int /*<<< orphan*/  rip_entry_print_v1 (TYPE_1__*,struct rip_netinfo const*) ; 
 int rip_entry_print_v2 (TYPE_1__*,struct rip_netinfo const*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 

void
rip_print(netdissect_options *ndo,
          const u_char *dat, u_int length)
{
	register const struct rip *rp;
	register const struct rip_netinfo *ni;
	register u_int i, j;

	if (ndo->ndo_snapend < dat) {
		ND_PRINT((ndo, " %s", tstr));
		return;
	}
	i = ndo->ndo_snapend - dat;
	if (i > length)
		i = length;
	if (i < sizeof(*rp)) {
		ND_PRINT((ndo, " %s", tstr));
		return;
	}
	i -= sizeof(*rp);

	rp = (const struct rip *)dat;

	ND_PRINT((ndo, "%sRIPv%u",
               (ndo->ndo_vflag >= 1) ? "\n\t" : "",
               rp->rip_vers));

	switch (rp->rip_vers) {
	case 0:
		/*
		 * RFC 1058.
		 *
		 * XXX - RFC 1058 says
		 *
		 * 0  Datagrams whose version number is zero are to be ignored.
		 *    These are from a previous version of the protocol, whose
		 *    packet format was machine-specific.
		 *
		 * so perhaps we should just dump the packet, in hex.
		 */
                print_unknown_data(ndo, (const uint8_t *)&rp->rip_cmd, "\n\t", length);
		break;
	default:
                /* dump version and lets see if we know the commands name*/
                ND_PRINT((ndo, ", %s, length: %u",
                       tok2str(rip_cmd_values,
                               "unknown command (%u)",
                               rp->rip_cmd),
                       length));

                if (ndo->ndo_vflag < 1)
                    return;

		switch (rp->rip_cmd) {
		case RIPCMD_REQUEST:
		case RIPCMD_RESPONSE:
			j = length / sizeof(*ni);
			ND_PRINT((ndo, ", routes: %u%s", j, rp->rip_vers == 2 ? " or less" : ""));
			ni = (const struct rip_netinfo *)(rp + 1);
			for (; i >= sizeof(*ni); ++ni) {
				if (rp->rip_vers == 1)
				{
					rip_entry_print_v1(ndo, ni);
					i -= sizeof(*ni);
				}
				else if (rp->rip_vers == 2)
					i -= rip_entry_print_v2(ndo, ni, i);
                                else
                                    break;
			}
			if (i)
				ND_PRINT((ndo, "%s", tstr));
			break;

		case RIPCMD_TRACEOFF:
		case RIPCMD_POLL:
		case RIPCMD_POLLENTRY:
			break;

		case RIPCMD_TRACEON:
                    /* fall through */
	        default:
                    if (ndo->ndo_vflag <= 1) {
                        if(!print_unknown_data(ndo, (const uint8_t *)rp, "\n\t", length))
                            return;
                    }
                    break;
                }
                /* do we want to see an additionally hexdump ? */
                if (ndo->ndo_vflag> 1) {
                    if(!print_unknown_data(ndo, (const uint8_t *)rp, "\n\t", length))
                        return;
                }
        }
}