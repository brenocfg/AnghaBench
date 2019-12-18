#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct netmap_priv_d {struct netmap_adapter* np_na; struct netmap_if* np_nifp; } ;
struct netmap_if {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  objsize; int /*<<< orphan*/  objtotal; int /*<<< orphan*/  lut; } ;
struct netmap_adapter {scalar_t__ active_fds; int (* nm_krings_create ) (struct netmap_adapter*) ;int (* nm_register ) (struct netmap_adapter*,int) ;TYPE_1__ na_lut; int /*<<< orphan*/  (* nm_krings_delete ) (struct netmap_adapter*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  rx_buf_maxsize; scalar_t__ ifp; int /*<<< orphan*/  nm_mem; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NETMAP_BUF_SIZE (struct netmap_adapter*) ; 
 int /*<<< orphan*/  NMG_LOCK_ASSERT () ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int netmap_buf_size_validate (struct netmap_adapter*,unsigned int) ; 
 int netmap_krings_get (struct netmap_priv_d*) ; 
 int /*<<< orphan*/  netmap_krings_put (struct netmap_priv_d*) ; 
 int /*<<< orphan*/  netmap_mem_drop (struct netmap_adapter*) ; 
 int netmap_mem_finalize (int /*<<< orphan*/ ,struct netmap_adapter*) ; 
 int netmap_mem_get_lut (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  netmap_mem_if_delete (struct netmap_adapter*,struct netmap_if*) ; 
 struct netmap_if* netmap_mem_if_new (struct netmap_adapter*,struct netmap_priv_d*) ; 
 int netmap_mem_rings_create (struct netmap_adapter*) ; 
 int /*<<< orphan*/  netmap_mem_rings_delete (struct netmap_adapter*) ; 
 int netmap_set_ringid (struct netmap_priv_d*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netmap_update_config (struct netmap_adapter*) ; 
 scalar_t__ nm_kring_pending (struct netmap_priv_d*) ; 
 unsigned int nm_os_ifnet_mtu (scalar_t__) ; 
 int /*<<< orphan*/  nm_prdis (char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  nm_prerr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nm_priv_rx_enabled (struct netmap_priv_d*) ; 
 int stub1 (struct netmap_adapter*) ; 
 int stub2 (struct netmap_adapter*,int) ; 
 int /*<<< orphan*/  stub3 (struct netmap_adapter*) ; 

int
netmap_do_regif(struct netmap_priv_d *priv, struct netmap_adapter *na,
	uint32_t nr_mode, uint16_t nr_ringid, uint64_t nr_flags)
{
	struct netmap_if *nifp = NULL;
	int error;

	NMG_LOCK_ASSERT();
	priv->np_na = na;     /* store the reference */
	error = netmap_mem_finalize(na->nm_mem, na);
	if (error)
		goto err;

	if (na->active_fds == 0) {

		/* cache the allocator info in the na */
		error = netmap_mem_get_lut(na->nm_mem, &na->na_lut);
		if (error)
			goto err_drop_mem;
		nm_prdis("lut %p bufs %u size %u", na->na_lut.lut, na->na_lut.objtotal,
					    na->na_lut.objsize);

		/* ring configuration may have changed, fetch from the card */
		netmap_update_config(na);
	}

	/* compute the range of tx and rx rings to monitor */
	error = netmap_set_ringid(priv, nr_mode, nr_ringid, nr_flags);
	if (error)
		goto err_put_lut;

	if (na->active_fds == 0) {
		/*
		 * If this is the first registration of the adapter,
		 * perform sanity checks and create the in-kernel view
		 * of the netmap rings (the netmap krings).
		 */
		if (na->ifp && nm_priv_rx_enabled(priv)) {
			/* This netmap adapter is attached to an ifnet. */
			unsigned mtu = nm_os_ifnet_mtu(na->ifp);

			nm_prdis("%s: mtu %d rx_buf_maxsize %d netmap_buf_size %d",
				na->name, mtu, na->rx_buf_maxsize, NETMAP_BUF_SIZE(na));

			if (na->rx_buf_maxsize == 0) {
				nm_prerr("%s: error: rx_buf_maxsize == 0", na->name);
				error = EIO;
				goto err_drop_mem;
			}

			error = netmap_buf_size_validate(na, mtu);
			if (error)
				goto err_drop_mem;
		}

		/*
		 * Depending on the adapter, this may also create
		 * the netmap rings themselves
		 */
		error = na->nm_krings_create(na);
		if (error)
			goto err_put_lut;

	}

	/* now the krings must exist and we can check whether some
	 * previous bind has exclusive ownership on them, and set
	 * nr_pending_mode
	 */
	error = netmap_krings_get(priv);
	if (error)
		goto err_del_krings;

	/* create all needed missing netmap rings */
	error = netmap_mem_rings_create(na);
	if (error)
		goto err_rel_excl;

	/* in all cases, create a new netmap if */
	nifp = netmap_mem_if_new(na, priv);
	if (nifp == NULL) {
		error = ENOMEM;
		goto err_rel_excl;
	}

	if (nm_kring_pending(priv)) {
		/* Some kring is switching mode, tell the adapter to
		 * react on this. */
		error = na->nm_register(na, 1);
		if (error)
			goto err_del_if;
	}

	/* Commit the reference. */
	na->active_fds++;

	/*
	 * advertise that the interface is ready by setting np_nifp.
	 * The barrier is needed because readers (poll, *SYNC and mmap)
	 * check for priv->np_nifp != NULL without locking
	 */
	mb(); /* make sure previous writes are visible to all CPUs */
	priv->np_nifp = nifp;

	return 0;

err_del_if:
	netmap_mem_if_delete(na, nifp);
err_rel_excl:
	netmap_krings_put(priv);
	netmap_mem_rings_delete(na);
err_del_krings:
	if (na->active_fds == 0)
		na->nm_krings_delete(na);
err_put_lut:
	if (na->active_fds == 0)
		memset(&na->na_lut, 0, sizeof(na->na_lut));
err_drop_mem:
	netmap_mem_drop(na);
err:
	priv->np_na = NULL;
	return error;
}