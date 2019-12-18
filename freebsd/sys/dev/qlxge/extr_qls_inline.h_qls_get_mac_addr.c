#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * mac_addr; } ;
typedef  TYPE_1__ qla_host_t ;

/* Variables and functions */

__attribute__((used)) static __inline uint8_t *
qls_get_mac_addr(qla_host_t *ha)
{
	return (ha->mac_addr);
}