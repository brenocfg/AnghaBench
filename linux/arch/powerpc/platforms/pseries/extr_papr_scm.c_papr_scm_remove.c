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
struct platform_device {int dummy; } ;
struct papr_scm_priv {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  drc_pmem_unbind (struct papr_scm_priv*) ; 
 int /*<<< orphan*/  kfree (struct papr_scm_priv*) ; 
 int /*<<< orphan*/  nvdimm_bus_unregister (int /*<<< orphan*/ ) ; 
 struct papr_scm_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int papr_scm_remove(struct platform_device *pdev)
{
	struct papr_scm_priv *p = platform_get_drvdata(pdev);

	nvdimm_bus_unregister(p->bus);
	drc_pmem_unbind(p);
	kfree(p);

	return 0;
}