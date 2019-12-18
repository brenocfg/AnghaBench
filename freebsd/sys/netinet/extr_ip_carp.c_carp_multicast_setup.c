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
struct ip_moptions {int imo_multicast_vif; int /*<<< orphan*/  imo_multicast_loop; void* imo_multicast_ttl; struct ifnet* imo_multicast_ifp; int /*<<< orphan*/  imo_head; } ;
struct ip6_moptions {int /*<<< orphan*/  im6o_head; struct ifnet* im6o_multicast_ifp; void* im6o_multicast_hlim; } ;
struct in_mfilter {int /*<<< orphan*/  imf_inm; } ;
struct in_addr {void* s_addr; } ;
struct in6_mfilter {int /*<<< orphan*/  im6f_in6m; } ;
struct in6_addr {int* s6_addr8; void** s6_addr32; void** s6_addr16; } ;
struct ifnet {int dummy; } ;
struct carp_if {struct ip6_moptions cif_im6o; struct ip_moptions cif_imo; struct ifnet* cif_ifp; } ;
typedef  int sa_family_t ;
typedef  int /*<<< orphan*/  in6 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 void* CARP_DFLTTL ; 
 int INADDR_CARP_GROUP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct in6_addr*,int) ; 
 void* htonl (int) ; 
 void* htons (int) ; 
 int in6_joingroup (struct ifnet*,struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_leavegroup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int in6_setscope (struct in6_addr*,struct ifnet*,int /*<<< orphan*/ *) ; 
 int in_joingroup (struct ifnet*,struct in_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct in6_mfilter* ip6_mfilter_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_mfilter_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_mfilter_free (struct in6_mfilter*) ; 
 int /*<<< orphan*/  ip6_mfilter_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_mfilter_insert (int /*<<< orphan*/ *,struct in6_mfilter*) ; 
 struct in_mfilter* ip_mfilter_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ip_mfilter_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_mfilter_free (struct in_mfilter*) ; 
 int /*<<< orphan*/  ip_mfilter_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_mfilter_insert (int /*<<< orphan*/ *,struct in_mfilter*) ; 

__attribute__((used)) static int
carp_multicast_setup(struct carp_if *cif, sa_family_t sa)
{
	struct ifnet *ifp = cif->cif_ifp;
	int error = 0;

	switch (sa) {
#ifdef INET
	case AF_INET:
	    {
		struct ip_moptions *imo = &cif->cif_imo;
		struct in_mfilter *imf;
		struct in_addr addr;

		if (ip_mfilter_first(&imo->imo_head) != NULL)
			return (0);

		imf = ip_mfilter_alloc(M_WAITOK, 0, 0);
		ip_mfilter_init(&imo->imo_head);
		imo->imo_multicast_vif = -1;

		addr.s_addr = htonl(INADDR_CARP_GROUP);
		if ((error = in_joingroup(ifp, &addr, NULL,
		    &imf->imf_inm)) != 0) {
			ip_mfilter_free(imf);
			break;
		}

		ip_mfilter_insert(&imo->imo_head, imf);
		imo->imo_multicast_ifp = ifp;
		imo->imo_multicast_ttl = CARP_DFLTTL;
		imo->imo_multicast_loop = 0;
		break;
	   }
#endif
#ifdef INET6
	case AF_INET6:
	    {
		struct ip6_moptions *im6o = &cif->cif_im6o;
		struct in6_mfilter *im6f[2];
		struct in6_addr in6;

		if (ip6_mfilter_first(&im6o->im6o_head))
			return (0);

		im6f[0] = ip6_mfilter_alloc(M_WAITOK, 0, 0);
		im6f[1] = ip6_mfilter_alloc(M_WAITOK, 0, 0);

		ip6_mfilter_init(&im6o->im6o_head);
		im6o->im6o_multicast_hlim = CARP_DFLTTL;
		im6o->im6o_multicast_ifp = ifp;

		/* Join IPv6 CARP multicast group. */
		bzero(&in6, sizeof(in6));
		in6.s6_addr16[0] = htons(0xff02);
		in6.s6_addr8[15] = 0x12;
		if ((error = in6_setscope(&in6, ifp, NULL)) != 0) {
			ip6_mfilter_free(im6f[0]);
			ip6_mfilter_free(im6f[1]);
			break;
		}
		if ((error = in6_joingroup(ifp, &in6, NULL, &im6f[0]->im6f_in6m, 0)) != 0) {
			ip6_mfilter_free(im6f[0]);
			ip6_mfilter_free(im6f[1]);
			break;
		}

		/* Join solicited multicast address. */
		bzero(&in6, sizeof(in6));
		in6.s6_addr16[0] = htons(0xff02);
		in6.s6_addr32[1] = 0;
		in6.s6_addr32[2] = htonl(1);
		in6.s6_addr32[3] = 0;
		in6.s6_addr8[12] = 0xff;

		if ((error = in6_setscope(&in6, ifp, NULL)) != 0) {
			ip6_mfilter_free(im6f[0]);
			ip6_mfilter_free(im6f[1]);
			break;
		}

		if ((error = in6_joingroup(ifp, &in6, NULL, &im6f[1]->im6f_in6m, 0)) != 0) {
			in6_leavegroup(im6f[0]->im6f_in6m, NULL);
			ip6_mfilter_free(im6f[0]);
			ip6_mfilter_free(im6f[1]);
			break;
		}
		ip6_mfilter_insert(&im6o->im6o_head, im6f[0]);
		ip6_mfilter_insert(&im6o->im6o_head, im6f[1]);
		break;
	    }
#endif
	}

	return (error);
}