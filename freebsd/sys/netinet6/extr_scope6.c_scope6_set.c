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
struct scope6_id {scalar_t__* s6id_list; } ;
struct ifnet {scalar_t__ if_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IF_AFDATA_WLOCK (struct ifnet*) ; 
 int /*<<< orphan*/  IF_AFDATA_WUNLOCK (struct ifnet*) ; 
 int IPV6_ADDR_SCOPE_INTFACELOCAL ; 
 int IPV6_ADDR_SCOPE_LINKLOCAL ; 
 struct scope6_id* SID (struct ifnet*) ; 
 scalar_t__ V_if_index ; 

__attribute__((used)) static int
scope6_set(struct ifnet *ifp, struct scope6_id *idlist)
{
	int i;
	int error = 0;
	struct scope6_id *sid = NULL;

	IF_AFDATA_WLOCK(ifp);
	sid = SID(ifp);

	if (!sid) {	/* paranoid? */
		IF_AFDATA_WUNLOCK(ifp);
		return (EINVAL);
	}

	/*
	 * XXX: We need more consistency checks of the relationship among
	 * scopes (e.g. an organization should be larger than a site).
	 */

	/*
	 * TODO(XXX): after setting, we should reflect the changes to
	 * interface addresses, routing table entries, PCB entries...
	 */

	for (i = 0; i < 16; i++) {
		if (idlist->s6id_list[i] &&
		    idlist->s6id_list[i] != sid->s6id_list[i]) {
			/*
			 * An interface zone ID must be the corresponding
			 * interface index by definition.
			 */
			if (i == IPV6_ADDR_SCOPE_INTFACELOCAL &&
			    idlist->s6id_list[i] != ifp->if_index) {
				IF_AFDATA_WUNLOCK(ifp);
				return (EINVAL);
			}

			if (i == IPV6_ADDR_SCOPE_LINKLOCAL &&
			    idlist->s6id_list[i] > V_if_index) {
				/*
				 * XXX: theoretically, there should be no
				 * relationship between link IDs and interface
				 * IDs, but we check the consistency for
				 * safety in later use.
				 */
				IF_AFDATA_WUNLOCK(ifp);
				return (EINVAL);
			}

			/*
			 * XXX: we must need lots of work in this case,
			 * but we simply set the new value in this initial
			 * implementation.
			 */
			sid->s6id_list[i] = idlist->s6id_list[i];
		}
	}
	IF_AFDATA_WUNLOCK(ifp);

	return (error);
}