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
struct ifbareq {int /*<<< orphan*/  ifba_vlan; int /*<<< orphan*/  ifba_dst; } ;
struct bridge_softc {int dummy; } ;

/* Variables and functions */
 int bridge_rtdaddr (struct bridge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bridge_ioctl_daddr(struct bridge_softc *sc, void *arg)
{
	struct ifbareq *req = arg;

	return (bridge_rtdaddr(sc, req->ifba_dst, req->ifba_vlan));
}