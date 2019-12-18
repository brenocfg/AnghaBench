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
struct TYPE_2__ {scalar_t__ nr_ringid; scalar_t__ nr_mode; int /*<<< orphan*/  nr_flags; } ;
struct nmreq_vale_attach {TYPE_1__ reg; } ;
struct nmreq_header {scalar_t__ nr_reqtype; scalar_t__ nr_body; } ;
struct netmap_priv_d {int /*<<< orphan*/  np_ifp; } ;
struct netmap_bwrap_adapter {struct netmap_priv_d* na_kpriv; } ;
struct netmap_adapter {scalar_t__ active_fds; int /*<<< orphan*/  na_flags; int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NAF_BUSY ; 
 scalar_t__ NETMAP_OWNED_BY_ANY (struct netmap_adapter*) ; 
 scalar_t__ NETMAP_REQ_VALE_ATTACH ; 
 scalar_t__ NR_REG_ALL_NIC ; 
 scalar_t__ NR_REG_NIC_SW ; 
 int netmap_do_regif (struct netmap_priv_d*,struct netmap_adapter*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netmap_priv_delete (struct netmap_priv_d*) ; 
 struct netmap_priv_d* netmap_priv_new () ; 

__attribute__((used)) static int
netmap_bwrap_bdg_ctl(struct nmreq_header *hdr, struct netmap_adapter *na)
{
	struct netmap_priv_d *npriv;
	struct netmap_bwrap_adapter *bna = (struct netmap_bwrap_adapter*)na;
	int error = 0;

	if (hdr->nr_reqtype == NETMAP_REQ_VALE_ATTACH) {
		struct nmreq_vale_attach *req =
			(struct nmreq_vale_attach *)(uintptr_t)hdr->nr_body;
		if (req->reg.nr_ringid != 0 ||
			(req->reg.nr_mode != NR_REG_ALL_NIC &&
				req->reg.nr_mode != NR_REG_NIC_SW)) {
			/* We only support attaching all the NIC rings
			 * and/or the host stack. */
			return EINVAL;
		}
		if (NETMAP_OWNED_BY_ANY(na)) {
			return EBUSY;
		}
		if (bna->na_kpriv) {
			/* nothing to do */
			return 0;
		}
		npriv = netmap_priv_new();
		if (npriv == NULL)
			return ENOMEM;
		npriv->np_ifp = na->ifp; /* let the priv destructor release the ref */
		error = netmap_do_regif(npriv, na, req->reg.nr_mode,
					req->reg.nr_ringid, req->reg.nr_flags);
		if (error) {
			netmap_priv_delete(npriv);
			return error;
		}
		bna->na_kpriv = npriv;
		na->na_flags |= NAF_BUSY;
	} else {
		if (na->active_fds == 0) /* not registered */
			return EINVAL;
		netmap_priv_delete(bna->na_kpriv);
		bna->na_kpriv = NULL;
		na->na_flags &= ~NAF_BUSY;
	}

	return error;
}