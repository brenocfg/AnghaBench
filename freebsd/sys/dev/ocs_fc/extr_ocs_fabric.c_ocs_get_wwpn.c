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
typedef  long long uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  port_name_lo; int /*<<< orphan*/  port_name_hi; } ;
typedef  TYPE_1__ fc_plogi_payload_t ;

/* Variables and functions */
 long long ocs_be32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
ocs_get_wwpn(fc_plogi_payload_t *sp)
{
	return (((uint64_t)ocs_be32toh(sp->port_name_hi) << 32ll) | (ocs_be32toh(sp->port_name_lo)));
}