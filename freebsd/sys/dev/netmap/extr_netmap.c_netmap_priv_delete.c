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
struct netmap_priv_d {scalar_t__ np_refs; int /*<<< orphan*/  np_ifp; struct netmap_adapter* np_na; } ;
struct netmap_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct netmap_priv_d*,int) ; 
 int /*<<< orphan*/  netmap_do_unregif (struct netmap_priv_d*) ; 
 int /*<<< orphan*/  netmap_unget_na (struct netmap_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_os_free (struct netmap_priv_d*) ; 
 int /*<<< orphan*/  nm_os_put_module () ; 

void
netmap_priv_delete(struct netmap_priv_d *priv)
{
	struct netmap_adapter *na = priv->np_na;

	/* number of active references to this fd */
	if (--priv->np_refs > 0) {
		return;
	}
	nm_os_put_module();
	if (na) {
		netmap_do_unregif(priv);
	}
	netmap_unget_na(na, priv->np_ifp);
	bzero(priv, sizeof(*priv));	/* for safety */
	nm_os_free(priv);
}