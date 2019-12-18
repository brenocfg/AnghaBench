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
typedef  int /*<<< orphan*/  uint32_t ;
struct ipsec_softc {int /*<<< orphan*/  reqid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct ipsec_softc*,int /*<<< orphan*/ ) ; 
 int EEXIST ; 
 int IPSEC_REQID_TRYCNT ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  idhash ; 
 scalar_t__ ipsec_check_reqid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_idhash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_ioctl_sx ; 
 int /*<<< orphan*/  key_newreqid () ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipsec_init_reqid(struct ipsec_softc *sc)
{
	uint32_t reqid;
	int trycount;

	sx_assert(&ipsec_ioctl_sx, SA_XLOCKED);
	if (sc->reqid != 0) /* already initialized */
		return (0);

	trycount = IPSEC_REQID_TRYCNT;
	while (--trycount > 0) {
		reqid = key_newreqid();
		if (ipsec_check_reqid(reqid) == 0)
			break;
	}
	if (trycount == 0)
		return (EEXIST);
	sc->reqid = reqid;
	CK_LIST_INSERT_HEAD(ipsec_idhash(reqid), sc, idhash);
	return (0);
}