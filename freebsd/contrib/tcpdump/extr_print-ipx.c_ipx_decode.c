#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ipxHdr {int /*<<< orphan*/  dstSkt; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
#define  IPX_SKT_DIAGNOSTICS 134 
#define  IPX_SKT_EIGRP 133 
#define  IPX_SKT_NCP 132 
#define  IPX_SKT_NETBIOS 131 
#define  IPX_SKT_NWLINK_DGM 130 
#define  IPX_SKT_RIP 129 
#define  IPX_SKT_SAP 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eigrp_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipx_netbios_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipx_rip_print (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipx_sap_print (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipx_decode(netdissect_options *ndo, const struct ipxHdr *ipx, const u_char *datap, u_int length)
{
    register u_short dstSkt;

    dstSkt = EXTRACT_16BITS(&ipx->dstSkt);
    switch (dstSkt) {
      case IPX_SKT_NCP:
	ND_PRINT((ndo, "ipx-ncp %d", length));
	break;
      case IPX_SKT_SAP:
	ipx_sap_print(ndo, (const u_short *)datap, length);
	break;
      case IPX_SKT_RIP:
	ipx_rip_print(ndo, (const u_short *)datap, length);
	break;
      case IPX_SKT_NETBIOS:
	ND_PRINT((ndo, "ipx-netbios %d", length));
#ifdef ENABLE_SMB
	ipx_netbios_print(ndo, datap, length);
#endif
	break;
      case IPX_SKT_DIAGNOSTICS:
	ND_PRINT((ndo, "ipx-diags %d", length));
	break;
      case IPX_SKT_NWLINK_DGM:
	ND_PRINT((ndo, "ipx-nwlink-dgm %d", length));
#ifdef ENABLE_SMB
	ipx_netbios_print(ndo, datap, length);
#endif
	break;
      case IPX_SKT_EIGRP:
	eigrp_print(ndo, datap, length);
	break;
      default:
	ND_PRINT((ndo, "ipx-#%x %d", dstSkt, length));
	break;
    }
}