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
typedef  int /*<<< orphan*/  u_int8_t ;
struct nd_ifinfo {int /*<<< orphan*/  const* randomid; int /*<<< orphan*/ * randomseed1; int /*<<< orphan*/  randomseed0; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  nullbuf ;

/* Variables and functions */
 struct nd_ifinfo* ND_IFINFO (struct ifnet*) ; 
 scalar_t__ bcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  generate_tmp_ifid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int
in6_get_tmpifid(struct ifnet *ifp, u_int8_t *retbuf,
    const u_int8_t *baseid, int generate)
{
	u_int8_t nullbuf[8];
	struct nd_ifinfo *ndi = ND_IFINFO(ifp);

	bzero(nullbuf, sizeof(nullbuf));
	if (bcmp(ndi->randomid, nullbuf, sizeof(nullbuf)) == 0) {
		/* we've never created a random ID.  Create a new one. */
		generate = 1;
	}

	if (generate) {
		bcopy(baseid, ndi->randomseed1, sizeof(ndi->randomseed1));

		/* generate_tmp_ifid will update seedn and buf */
		(void)generate_tmp_ifid(ndi->randomseed0, ndi->randomseed1,
		    ndi->randomid);
	}
	bcopy(ndi->randomid, retbuf, 8);

	return (0);
}