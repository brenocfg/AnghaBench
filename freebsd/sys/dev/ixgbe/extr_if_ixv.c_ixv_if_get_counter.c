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
struct adapter {int /*<<< orphan*/  imcasts; int /*<<< orphan*/  obytes; int /*<<< orphan*/  ibytes; int /*<<< orphan*/  opackets; int /*<<< orphan*/  ipackets; } ;
typedef  int ift_counter ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
#define  IFCOUNTER_IBYTES 132 
#define  IFCOUNTER_IMCASTS 131 
#define  IFCOUNTER_IPACKETS 130 
#define  IFCOUNTER_OBYTES 129 
#define  IFCOUNTER_OPACKETS 128 
 int /*<<< orphan*/  if_get_counter_default (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
ixv_if_get_counter(if_ctx_t ctx, ift_counter cnt)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	if_t           ifp = iflib_get_ifp(ctx);

	switch (cnt) {
	case IFCOUNTER_IPACKETS:
		return (adapter->ipackets);
	case IFCOUNTER_OPACKETS:
		return (adapter->opackets);
	case IFCOUNTER_IBYTES:
		return (adapter->ibytes);
	case IFCOUNTER_OBYTES:
		return (adapter->obytes);
	case IFCOUNTER_IMCASTS:
		return (adapter->imcasts);
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}