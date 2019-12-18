#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {size_t if_type; int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
typedef  size_t sli4_regname_e ;
struct TYPE_6__ {scalar_t__ rset; scalar_t__ off; } ;
typedef  TYPE_2__ sli4_reg_t ;

/* Variables and functions */
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/  ocs_reg_write32 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__** regmap ; 

void
sli_reg_write(sli4_t *sli, sli4_regname_e reg, uint32_t val)
{
	const sli4_reg_t	*r = &(regmap[reg][sli->if_type]);

	if ((UINT32_MAX == r->rset) || (UINT32_MAX == r->off)) {
		ocs_log_err(sli->os, "regname %d not defined for if_type %d\n", reg, sli->if_type);
		return;
	}

	ocs_reg_write32(sli->os, r->rset, r->off, val);
}