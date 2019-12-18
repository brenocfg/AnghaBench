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
struct ip6_moptions {int /*<<< orphan*/  im6o_head; } ;
struct in6_multi {struct ifnet* in6m_ifp; } ;
struct in6_mfilter {struct in6_multi* im6f_in6m; } ;
struct ifnet {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IP6MOPTS ; 
 int /*<<< orphan*/  free (struct ip6_moptions*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  im6f_leave (struct in6_mfilter*) ; 
 int /*<<< orphan*/  in6_leavegroup (struct in6_multi*,struct in6_mfilter*) ; 
 struct in6_mfilter* ip6_mfilter_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_mfilter_free (struct in6_mfilter*) ; 
 int /*<<< orphan*/  ip6_mfilter_remove (int /*<<< orphan*/ *,struct in6_mfilter*) ; 

__attribute__((used)) static void
inp_gcmoptions(struct ip6_moptions *imo)
{
	struct in6_mfilter *imf;
	struct in6_multi *inm;
	struct ifnet *ifp;

	while ((imf = ip6_mfilter_first(&imo->im6o_head)) != NULL) {
                ip6_mfilter_remove(&imo->im6o_head, imf);

                im6f_leave(imf);
                if ((inm = imf->im6f_in6m) != NULL) {
                        if ((ifp = inm->in6m_ifp) != NULL) {
                                CURVNET_SET(ifp->if_vnet);
                                (void)in6_leavegroup(inm, imf);
                                CURVNET_RESTORE();
                        } else {
                                (void)in6_leavegroup(inm, imf);
                        }
                }
                ip6_mfilter_free(imf);
        }
        free(imo, M_IP6MOPTS);
}