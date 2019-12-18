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
struct pfi_dynaddr {int /*<<< orphan*/  pfid_kt; int /*<<< orphan*/  pfid_mask6; int /*<<< orphan*/  pfid_addr6; int /*<<< orphan*/  pfid_acnt6; int /*<<< orphan*/  pfid_mask4; int /*<<< orphan*/  pfid_addr4; int /*<<< orphan*/  pfid_acnt4; } ;
struct pf_addr {int dummy; } ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int PF_MATCHA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct pf_addr*,int const) ; 
 int pfr_match_addr (int /*<<< orphan*/ ,struct pf_addr*,int const) ; 

int
pfi_match_addr(struct pfi_dynaddr *dyn, struct pf_addr *a, sa_family_t af)
{
	switch (af) {
#ifdef INET
	case AF_INET:
		switch (dyn->pfid_acnt4) {
		case 0:
			return (0);
		case 1:
			return (PF_MATCHA(0, &dyn->pfid_addr4,
			    &dyn->pfid_mask4, a, AF_INET));
		default:
			return (pfr_match_addr(dyn->pfid_kt, a, AF_INET));
		}
		break;
#endif /* INET */
#ifdef INET6
	case AF_INET6:
		switch (dyn->pfid_acnt6) {
		case 0:
			return (0);
		case 1:
			return (PF_MATCHA(0, &dyn->pfid_addr6,
			    &dyn->pfid_mask6, a, AF_INET6));
		default:
			return (pfr_match_addr(dyn->pfid_kt, a, AF_INET6));
		}
		break;
#endif /* INET6 */
	default:
		return (0);
	}
}