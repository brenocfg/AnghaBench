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
struct vmbus_softc {int dummy; } ;

/* Variables and functions */
 struct vmbus_softc* vmbus_sc ; 

__attribute__((used)) static __inline struct vmbus_softc *
vmbus_get_softc(void)
{
	return vmbus_sc;
}