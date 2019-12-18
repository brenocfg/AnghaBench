#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* buf; int /*<<< orphan*/  nports; } ;
typedef  TYPE_1__ isc_portset_t ;
typedef  int in_port_t ;

/* Variables and functions */
 scalar_t__ portset_isset (TYPE_1__*,int) ; 

__attribute__((used)) static inline void
portset_remove(isc_portset_t *portset, in_port_t port) {
	if (portset_isset(portset, port)) {
		portset->nports--;
		portset->buf[port >> 5] &= ~(1 << (port & 31));
	}
}