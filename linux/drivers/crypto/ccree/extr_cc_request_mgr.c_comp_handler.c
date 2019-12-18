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
typedef  int u32 ;
struct device {int dummy; } ;
struct cc_req_mgr_handle {scalar_t__ axi_completed; } ;
struct cc_drvdata {int irq; int comp_mask; struct cc_req_mgr_handle* request_mgr_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_ICR ; 
 int /*<<< orphan*/  HOST_IMR ; 
 int /*<<< orphan*/  HOST_IRR ; 
 scalar_t__ cc_axi_comp_count (struct cc_drvdata*) ; 
 int cc_ioread (struct cc_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_iowrite (struct cc_drvdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cc_proc_backlog (struct cc_drvdata*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  proc_completions (struct cc_drvdata*) ; 

__attribute__((used)) static void comp_handler(unsigned long devarg)
{
	struct cc_drvdata *drvdata = (struct cc_drvdata *)devarg;
	struct cc_req_mgr_handle *request_mgr_handle =
						drvdata->request_mgr_handle;
	struct device *dev = drvdata_to_dev(drvdata);
	u32 irq;

	dev_dbg(dev, "Completion handler called!\n");
	irq = (drvdata->irq & drvdata->comp_mask);

	/* To avoid the interrupt from firing as we unmask it,
	 * we clear it now
	 */
	cc_iowrite(drvdata, CC_REG(HOST_ICR), irq);

	/* Avoid race with above clear: Test completion counter once more */

	request_mgr_handle->axi_completed += cc_axi_comp_count(drvdata);

	dev_dbg(dev, "AXI completion after updated: %d\n",
		request_mgr_handle->axi_completed);

	while (request_mgr_handle->axi_completed) {
		do {
			drvdata->irq |= cc_ioread(drvdata, CC_REG(HOST_IRR));
			irq = (drvdata->irq & drvdata->comp_mask);
			proc_completions(drvdata);

			/* At this point (after proc_completions()),
			 * request_mgr_handle->axi_completed is 0.
			 */
			request_mgr_handle->axi_completed +=
						cc_axi_comp_count(drvdata);
		} while (request_mgr_handle->axi_completed > 0);

		cc_iowrite(drvdata, CC_REG(HOST_ICR), irq);

		request_mgr_handle->axi_completed += cc_axi_comp_count(drvdata);
	}

	/* after verifing that there is nothing to do,
	 * unmask AXI completion interrupt
	 */
	cc_iowrite(drvdata, CC_REG(HOST_IMR),
		   cc_ioread(drvdata, CC_REG(HOST_IMR)) & ~drvdata->comp_mask);

	cc_proc_backlog(drvdata);
	dev_dbg(dev, "Comp. handler done.\n");
}