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
typedef  int /*<<< orphan*/  uint64_t ;
struct ixl_vsi {int /*<<< orphan*/  noproto; int /*<<< orphan*/  oqdrops; int /*<<< orphan*/  iqdrops; int /*<<< orphan*/  omcasts; int /*<<< orphan*/  imcasts; int /*<<< orphan*/  obytes; int /*<<< orphan*/  ibytes; int /*<<< orphan*/  oerrors; int /*<<< orphan*/  opackets; int /*<<< orphan*/  ierrors; int /*<<< orphan*/  ipackets; } ;
struct iavf_sc {struct ixl_vsi vsi; } ;
typedef  int ift_counter ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
#define  IFCOUNTER_COLLISIONS 139 
#define  IFCOUNTER_IBYTES 138 
#define  IFCOUNTER_IERRORS 137 
#define  IFCOUNTER_IMCASTS 136 
#define  IFCOUNTER_IPACKETS 135 
#define  IFCOUNTER_IQDROPS 134 
#define  IFCOUNTER_NOPROTO 133 
#define  IFCOUNTER_OBYTES 132 
#define  IFCOUNTER_OERRORS 131 
#define  IFCOUNTER_OMCASTS 130 
#define  IFCOUNTER_OPACKETS 129 
#define  IFCOUNTER_OQDROPS 128 
 int /*<<< orphan*/  if_get_counter_default (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct iavf_sc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
iavf_if_get_counter(if_ctx_t ctx, ift_counter cnt)
{
	struct iavf_sc *sc = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &sc->vsi;
	if_t ifp = iflib_get_ifp(ctx);

	switch (cnt) {
	case IFCOUNTER_IPACKETS:
		return (vsi->ipackets);
	case IFCOUNTER_IERRORS:
		return (vsi->ierrors);
	case IFCOUNTER_OPACKETS:
		return (vsi->opackets);
	case IFCOUNTER_OERRORS:
		return (vsi->oerrors);
	case IFCOUNTER_COLLISIONS:
		/* Collisions are by standard impossible in 40G/10G Ethernet */
		return (0);
	case IFCOUNTER_IBYTES:
		return (vsi->ibytes);
	case IFCOUNTER_OBYTES:
		return (vsi->obytes);
	case IFCOUNTER_IMCASTS:
		return (vsi->imcasts);
	case IFCOUNTER_OMCASTS:
		return (vsi->omcasts);
	case IFCOUNTER_IQDROPS:
		return (vsi->iqdrops);
	case IFCOUNTER_OQDROPS:
		return (vsi->oqdrops);
	case IFCOUNTER_NOPROTO:
		return (vsi->noproto);
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}