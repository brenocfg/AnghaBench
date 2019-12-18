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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  sa; } ;
struct TYPE_3__ {int /*<<< orphan*/  sa; } ;
struct secasindex {TYPE_2__ dst; TYPE_1__ src; } ;
struct ipsec_softc {scalar_t__ reqid; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct ipsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CK_LIST_REMOVE (struct ipsec_softc*,int /*<<< orphan*/ ) ; 
 int EEXIST ; 
 int /*<<< orphan*/  IPSEC_DIR_OUTBOUND ; 
 int /*<<< orphan*/  IPSEC_WAIT () ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  idhash ; 
 scalar_t__ ipsec_check_reqid (scalar_t__) ; 
 struct secasindex* ipsec_getsaidx (struct ipsec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_idhash (scalar_t__) ; 
 scalar_t__ ipsec_init_reqid (struct ipsec_softc*) ; 
 int /*<<< orphan*/  ipsec_ioctl_sx ; 
 int ipsec_set_tunnel (struct ipsec_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipsec_set_reqid(struct ipsec_softc *sc, uint32_t reqid)
{
	struct secasindex *saidx;

	sx_assert(&ipsec_ioctl_sx, SA_XLOCKED);

	if (sc->reqid == reqid && reqid != 0)
		return (0);

	if (reqid != 0) {
		/* Check that specified reqid doesn't exist */
		if (ipsec_check_reqid(reqid) != 0)
			return (EEXIST);
		if (sc->reqid != 0) {
			CK_LIST_REMOVE(sc, idhash);
			IPSEC_WAIT();
		}
		sc->reqid = reqid;
		CK_LIST_INSERT_HEAD(ipsec_idhash(reqid), sc, idhash);
	} else {
		/* Generate new reqid */
		if (ipsec_init_reqid(sc) != 0)
			return (EEXIST);
	}

	/* Tunnel isn't fully configured, just return. */
	if (sc->family == 0)
		return (0);

	saidx = ipsec_getsaidx(sc, IPSEC_DIR_OUTBOUND, sc->family);
	KASSERT(saidx != NULL,
	    ("saidx is NULL, but family is %d", sc->family));
	return (ipsec_set_tunnel(sc, &saidx->src.sa, &saidx->dst.sa,
	    sc->reqid));
}