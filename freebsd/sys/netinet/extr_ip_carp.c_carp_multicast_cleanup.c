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
struct ip_moptions {int /*<<< orphan*/  imo_head; } ;
struct ip6_moptions {int /*<<< orphan*/  im6o_head; } ;
struct in_mfilter {int /*<<< orphan*/  imf_inm; } ;
struct in6_mfilter {int /*<<< orphan*/  im6f_in6m; } ;
struct carp_if {int /*<<< orphan*/  cif_naddrs6; int /*<<< orphan*/  cif_naddrs; struct ip6_moptions cif_im6o; struct ip_moptions cif_imo; } ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  carp_sx ; 
 int /*<<< orphan*/  in6_leavegroup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_leavegroup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct in6_mfilter* ip6_mfilter_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_mfilter_free (struct in6_mfilter*) ; 
 int /*<<< orphan*/  ip6_mfilter_remove (int /*<<< orphan*/ *,struct in6_mfilter*) ; 
 struct in_mfilter* ip_mfilter_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_mfilter_free (struct in_mfilter*) ; 
 int /*<<< orphan*/  ip_mfilter_remove (int /*<<< orphan*/ *,struct in_mfilter*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
carp_multicast_cleanup(struct carp_if *cif, sa_family_t sa)
{
#ifdef INET
	struct ip_moptions *imo = &cif->cif_imo;
	struct in_mfilter *imf;
#endif
#ifdef INET6
	struct ip6_moptions *im6o = &cif->cif_im6o;
	struct in6_mfilter *im6f;
#endif
	sx_assert(&carp_sx, SA_XLOCKED);

	switch (sa) {
#ifdef INET
	case AF_INET:
		if (cif->cif_naddrs != 0)
			break;

		while ((imf = ip_mfilter_first(&imo->imo_head)) != NULL) {
			ip_mfilter_remove(&imo->imo_head, imf);
			in_leavegroup(imf->imf_inm, NULL);
			ip_mfilter_free(imf);
		}
		break;
#endif
#ifdef INET6
	case AF_INET6:
		if (cif->cif_naddrs6 != 0)
			break;

		while ((im6f = ip6_mfilter_first(&im6o->im6o_head)) != NULL) {
			ip6_mfilter_remove(&im6o->im6o_head, im6f);
			in6_leavegroup(im6f->im6f_in6m, NULL);
			ip6_mfilter_free(im6f);
		}
		break;
#endif
	}
}