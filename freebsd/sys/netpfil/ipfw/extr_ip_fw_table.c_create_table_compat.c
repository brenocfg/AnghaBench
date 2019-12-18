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
typedef  int /*<<< orphan*/  xi ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tid_info {int dummy; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vmask; } ;
typedef  TYPE_1__ ipfw_xtable_info ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_VTYPE_LEGACY ; 
 int create_table_internal (struct ip_fw_chain*,struct tid_info*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
create_table_compat(struct ip_fw_chain *ch, struct tid_info *ti,
    uint16_t *pkidx)
{
	ipfw_xtable_info xi;
	int error;

	memset(&xi, 0, sizeof(xi));
	/* Set default value mask for legacy clients */
	xi.vmask = IPFW_VTYPE_LEGACY;

	error = create_table_internal(ch, ti, NULL, &xi, pkidx, 1);
	if (error != 0)
		return (error);

	return (0);
}