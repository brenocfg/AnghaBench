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
struct pfi_kif {scalar_t__ pfik_tzero; } ;
struct epoch_tracker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 struct pfi_kif* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pfi_kif* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfi_kif*) ; 
 int /*<<< orphan*/  V_pfi_ifs ; 
 int /*<<< orphan*/  bcopy (struct pfi_kif*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfi_ifhead ; 
 scalar_t__ pfi_skip_if (char const*,struct pfi_kif*) ; 
 scalar_t__ time_second ; 

void
pfi_get_ifaces(const char *name, struct pfi_kif *buf, int *size)
{
	struct epoch_tracker et;
	struct pfi_kif	*p, *nextp;
	int		 n = 0;

	NET_EPOCH_ENTER(et);
	for (p = RB_MIN(pfi_ifhead, &V_pfi_ifs); p; p = nextp) {
		nextp = RB_NEXT(pfi_ifhead, &V_pfi_ifs, p);
		if (pfi_skip_if(name, p))
			continue;
		if (*size <= n++)
			break;
		if (!p->pfik_tzero)
			p->pfik_tzero = time_second;
		bcopy(p, buf++, sizeof(*buf));
		nextp = RB_NEXT(pfi_ifhead, &V_pfi_ifs, p);
	}
	*size = n;
	NET_EPOCH_EXIT(et);
}