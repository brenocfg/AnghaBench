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
struct OpalIoP7IOCErrorData {scalar_t__ lemWof; scalar_t__ lemAction1; scalar_t__ lemAction0; scalar_t__ lemErrMask; scalar_t__ lemFir; scalar_t__ gemRwof; scalar_t__ gemMask; scalar_t__ gemRirqfir; scalar_t__ gemRfir; scalar_t__ gemXfir; } ;

/* Variables and functions */
 int /*<<< orphan*/  be64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnv_eeh_dump_hub_diag_common(struct OpalIoP7IOCErrorData *data)
{
	/* GEM */
	if (data->gemXfir || data->gemRfir ||
	    data->gemRirqfir || data->gemMask || data->gemRwof)
		pr_info("  GEM: %016llx %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->gemXfir),
			be64_to_cpu(data->gemRfir),
			be64_to_cpu(data->gemRirqfir),
			be64_to_cpu(data->gemMask),
			be64_to_cpu(data->gemRwof));

	/* LEM */
	if (data->lemFir || data->lemErrMask ||
	    data->lemAction0 || data->lemAction1 || data->lemWof)
		pr_info("  LEM: %016llx %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->lemFir),
			be64_to_cpu(data->lemErrMask),
			be64_to_cpu(data->lemAction0),
			be64_to_cpu(data->lemAction1),
			be64_to_cpu(data->lemWof));
}