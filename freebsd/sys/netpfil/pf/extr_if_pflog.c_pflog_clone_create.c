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
struct TYPE_2__ {int /*<<< orphan*/  ifq_maxlen; } ;
struct ifnet {int /*<<< orphan*/  if_hdrlen; TYPE_1__ if_snd; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_output; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_mtu; } ;
struct if_clone {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_PFLOG ; 
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IFT_PFLOG ; 
 int PFLOGIFS_MAX ; 
 int /*<<< orphan*/  PFLOGMTU ; 
 int /*<<< orphan*/  PFLOG_HDRLEN ; 
 struct ifnet** V_pflogifs ; 
 int /*<<< orphan*/  bpfattach (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  pflogioctl ; 
 int /*<<< orphan*/  pflogname ; 
 int /*<<< orphan*/  pflogoutput ; 
 int /*<<< orphan*/  pflogstart ; 

__attribute__((used)) static int
pflog_clone_create(struct if_clone *ifc, int unit, caddr_t param)
{
	struct ifnet *ifp;

	if (unit >= PFLOGIFS_MAX)
		return (EINVAL);

	ifp = if_alloc(IFT_PFLOG);
	if (ifp == NULL) {
		return (ENOSPC);
	}
	if_initname(ifp, pflogname, unit);
	ifp->if_mtu = PFLOGMTU;
	ifp->if_ioctl = pflogioctl;
	ifp->if_output = pflogoutput;
	ifp->if_start = pflogstart;
	ifp->if_snd.ifq_maxlen = ifqmaxlen;
	ifp->if_hdrlen = PFLOG_HDRLEN;
	if_attach(ifp);

	bpfattach(ifp, DLT_PFLOG, PFLOG_HDRLEN);

	V_pflogifs[unit] = ifp;

	return (0);
}