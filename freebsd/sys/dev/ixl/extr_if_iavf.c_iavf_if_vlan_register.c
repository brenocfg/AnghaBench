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
typedef  int u16 ;
struct ixl_vsi {int /*<<< orphan*/  num_vlans; } ;
struct iavf_vlan_filter {int vlan; int /*<<< orphan*/  flags; } ;
struct iavf_sc {int /*<<< orphan*/  vlan_filters; struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_FLAG_AQ_ADD_VLAN_FILTER ; 
 int /*<<< orphan*/  IXL_FILTER_ADD ; 
 int /*<<< orphan*/  M_IAVF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ ,struct iavf_vlan_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_send_vc_msg (struct iavf_sc*,int /*<<< orphan*/ ) ; 
 struct iavf_sc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 struct iavf_vlan_filter* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
iavf_if_vlan_register(if_ctx_t ctx, u16 vtag)
{
	struct iavf_sc *sc = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &sc->vsi;
	struct iavf_vlan_filter	*v;

	if ((vtag == 0) || (vtag > 4095))	/* Invalid */
		return;

	++vsi->num_vlans;
	v = malloc(sizeof(struct iavf_vlan_filter), M_IAVF, M_WAITOK | M_ZERO);
	SLIST_INSERT_HEAD(sc->vlan_filters, v, next);
	v->vlan = vtag;
	v->flags = IXL_FILTER_ADD;

	iavf_send_vc_msg(sc, IAVF_FLAG_AQ_ADD_VLAN_FILTER);
}