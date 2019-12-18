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
struct in_multi {struct ifnet* inm_ifp; } ;
struct in_mfilter {struct in_multi* imf_inm; } ;
struct ifnet {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IPMOPTS ; 
 int /*<<< orphan*/  free (struct ip_moptions*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imf_leave (struct in_mfilter*) ; 
 int /*<<< orphan*/  in_leavegroup (struct in_multi*,struct in_mfilter*) ; 
 struct in_mfilter* ip_mfilter_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_mfilter_free (struct in_mfilter*) ; 
 int /*<<< orphan*/  ip_mfilter_remove (int /*<<< orphan*/ *,struct in_mfilter*) ; 

__attribute__((used)) static void
inp_gcmoptions(struct ip_moptions *imo)
{
	struct in_mfilter *imf;
	struct in_multi *inm;
	struct ifnet *ifp;

	while ((imf = ip_mfilter_first(&imo->imo_head)) != NULL) {
		ip_mfilter_remove(&imo->imo_head, imf);

		imf_leave(imf);
		if ((inm = imf->imf_inm) != NULL) {
			if ((ifp = inm->inm_ifp) != NULL) {
				CURVNET_SET(ifp->if_vnet);
				(void)in_leavegroup(inm, imf);
				CURVNET_RESTORE();
			} else {
				(void)in_leavegroup(inm, imf);
			}
		}
		ip_mfilter_free(imf);
	}
	free(imo, M_IPMOPTS);
}