#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct sockaddr {scalar_t__ sa_family; } ;
struct secpolicy {int dummy; } ;
struct ipsec_softc {scalar_t__ family; TYPE_1__* ifp; struct secpolicy** sp; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct ipsec_softc*,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IPSEC_SPCOUNT ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  ipsec_delete_tunnel (struct ipsec_softc*) ; 
 int /*<<< orphan*/  ipsec_ioctl_sx ; 
 scalar_t__ ipsec_newpolicies (struct ipsec_softc*,struct secpolicy**,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_set_running (struct ipsec_softc*) ; 
 int /*<<< orphan*/  ipsec_srchash (struct sockaddr*) ; 
 int /*<<< orphan*/  key_freesp (struct secpolicy**) ; 
 scalar_t__ key_register_ifnet (struct secpolicy**,int) ; 
 int /*<<< orphan*/  srchash ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipsec_set_tunnel(struct ipsec_softc *sc, struct sockaddr *src,
    struct sockaddr *dst, uint32_t reqid)
{
	struct secpolicy *sp[IPSEC_SPCOUNT];
	int i;

	sx_assert(&ipsec_ioctl_sx, SA_XLOCKED);

	/* Allocate SP with new addresses. */
	if (ipsec_newpolicies(sc, sp, src, dst, reqid) == 0) {
		/* Add new policies to SPDB */
		if (key_register_ifnet(sp, IPSEC_SPCOUNT) != 0) {
			for (i = 0; i < IPSEC_SPCOUNT; i++)
				key_freesp(&sp[i]);
			return (EAGAIN);
		}
		if (sc->family != 0)
			ipsec_delete_tunnel(sc);
		for (i = 0; i < IPSEC_SPCOUNT; i++)
			sc->sp[i] = sp[i];
		sc->family = src->sa_family;
		CK_LIST_INSERT_HEAD(ipsec_srchash(src), sc, srchash);
	} else {
		sc->ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		return (ENOMEM);
	}
	ipsec_set_running(sc);
	return (0);
}