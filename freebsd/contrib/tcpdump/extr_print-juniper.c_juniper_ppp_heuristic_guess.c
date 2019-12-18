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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
#define  PPP_CHAP 140 
#define  PPP_IP 139 
#define  PPP_IPCP 138 
#define  PPP_IPV6 137 
#define  PPP_IPV6CP 136 
#define  PPP_LCP 135 
#define  PPP_ML 134 
#define  PPP_MPLSCP 133 
#define  PPP_MPLS_MCAST 132 
#define  PPP_MPLS_UCAST 131 
#define  PPP_OSI 130 
#define  PPP_OSICP 129 
#define  PPP_PAP 128 
 int /*<<< orphan*/  ppp_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
juniper_ppp_heuristic_guess(netdissect_options *ndo,
                            register const u_char *p, u_int length)
{
    switch(EXTRACT_16BITS(p)) {
    case PPP_IP :
    case PPP_OSI :
    case PPP_MPLS_UCAST :
    case PPP_MPLS_MCAST :
    case PPP_IPCP :
    case PPP_OSICP :
    case PPP_MPLSCP :
    case PPP_LCP :
    case PPP_PAP :
    case PPP_CHAP :
    case PPP_ML :
    case PPP_IPV6 :
    case PPP_IPV6CP :
        ppp_print(ndo, p, length);
        break;

    default:
        return 0; /* did not find a ppp header */
        break;
    }
    return 1; /* we printed a ppp packet */
}