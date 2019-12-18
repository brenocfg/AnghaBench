#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ first_time; } ;
typedef  TYPE_1__ unit_t ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIVE ; 
 int /*<<< orphan*/  close_with_IOP (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ find_unit_by_fd (int /*<<< orphan*/ ,int*,int*,TYPE_1__**) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_2__*) ; 

__attribute__((used)) static void pcap_cleanup_acn(pcap_t *handle) {
	int		chassis, geoslot;
	unit_t	*u;

	if (find_unit_by_fd(handle->fd, &chassis, &geoslot, &u) == 0)
		return;
	close_with_IOP(chassis, geoslot, LIVE);
	if (u)
		u->first_time = 0;
	pcap_cleanup_live_common(handle);
}