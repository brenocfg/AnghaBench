#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ major; scalar_t__ minor; } ;
struct TYPE_4__ {TYPE_1__ ver; } ;
struct vdc_port {TYPE_2__ vio; } ;

/* Variables and functions */

__attribute__((used)) static inline int vdc_version_supported(struct vdc_port *port,
					u16 major, u16 minor)
{
	return port->vio.ver.major == major && port->vio.ver.minor >= minor;
}