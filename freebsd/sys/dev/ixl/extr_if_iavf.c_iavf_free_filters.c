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
struct iavf_vlan_filter {int dummy; } ;
struct iavf_sc {struct iavf_vlan_filter* vlan_filters; struct iavf_vlan_filter* mac_filters; } ;
typedef  struct iavf_vlan_filter iavf_mac_filter ;

/* Variables and functions */
 int /*<<< orphan*/  M_IAVF ; 
 int /*<<< orphan*/  SLIST_EMPTY (struct iavf_vlan_filter*) ; 
 struct iavf_vlan_filter* SLIST_FIRST (struct iavf_vlan_filter*) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (struct iavf_vlan_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct iavf_vlan_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
iavf_free_filters(struct iavf_sc *sc)
{
	struct iavf_mac_filter *f;
	struct iavf_vlan_filter *v;

	while (!SLIST_EMPTY(sc->mac_filters)) {
		f = SLIST_FIRST(sc->mac_filters);
		SLIST_REMOVE_HEAD(sc->mac_filters, next);
		free(f, M_IAVF);
	}
	free(sc->mac_filters, M_IAVF);
	while (!SLIST_EMPTY(sc->vlan_filters)) {
		v = SLIST_FIRST(sc->vlan_filters);
		SLIST_REMOVE_HEAD(sc->vlan_filters, next);
		free(v, M_IAVF);
	}
	free(sc->vlan_filters, M_IAVF);
}