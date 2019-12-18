#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa; } ;
struct TYPE_3__ {int /*<<< orphan*/  sa; } ;
struct secasindex {scalar_t__ reqid; TYPE_2__ dst; TYPE_1__ src; } ;
struct ipsec_softc {scalar_t__ family; scalar_t__ reqid; } ;
struct ifnet {struct ipsec_softc* if_softc; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  IPSEC_DIR_OUTBOUND ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 struct secasindex* ipsec_getsaidx (struct ipsec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipsec_init_reqid (struct ipsec_softc*) ; 
 int /*<<< orphan*/  ipsec_ioctl_sx ; 
 int ipsec_set_tunnel (struct ipsec_softc*,struct sockaddr*,struct sockaddr*,scalar_t__) ; 
 scalar_t__ key_sockaddrcmp (int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipsec_set_addresses(struct ifnet *ifp, struct sockaddr *src,
    struct sockaddr *dst)
{
	struct ipsec_softc *sc;
	struct secasindex *saidx;

	sx_assert(&ipsec_ioctl_sx, SA_XLOCKED);

	sc = ifp->if_softc;
	if (sc->family != 0) {
		saidx = ipsec_getsaidx(sc, IPSEC_DIR_OUTBOUND,
		    src->sa_family);
		if (saidx != NULL && saidx->reqid == sc->reqid &&
		    key_sockaddrcmp(&saidx->src.sa, src, 0) == 0 &&
		    key_sockaddrcmp(&saidx->dst.sa, dst, 0) == 0)
			return (0); /* Nothing has been changed. */

	}
	/* If reqid is not set, generate new one. */
	if (ipsec_init_reqid(sc) != 0)
		return (EEXIST);
	return (ipsec_set_tunnel(sc, src, dst, sc->reqid));
}