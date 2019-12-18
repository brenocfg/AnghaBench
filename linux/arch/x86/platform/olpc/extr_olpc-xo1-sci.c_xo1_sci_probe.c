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
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CS5536_GPIOM6_PME_EN ; 
 int CS5536_GPIOM7_PME_EN ; 
 scalar_t__ CS5536_PM_GPE0_EN ; 
 scalar_t__ CS5536_PM_GPE0_STS ; 
 int /*<<< orphan*/  EC_SCI_SRC_ALL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ acpi_base ; 
 int /*<<< orphan*/  detect_lid_state () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_ebook_switch () ; 
 int /*<<< orphan*/  free_ec_sci () ; 
 int /*<<< orphan*/  free_lid_events () ; 
 int /*<<< orphan*/  free_lid_switch () ; 
 int /*<<< orphan*/  free_power_button () ; 
 int /*<<< orphan*/  machine_is_olpc () ; 
 int mfd_cell_enable (struct platform_device*) ; 
 int /*<<< orphan*/  olpc_ec_mask_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_sci_queue (int) ; 
 int /*<<< orphan*/  send_ebook_state () ; 
 int /*<<< orphan*/  send_lid_state () ; 
 int setup_ebook_switch (struct platform_device*) ; 
 int setup_ec_sci () ; 
 int setup_lid_events () ; 
 int setup_lid_switch (struct platform_device*) ; 
 int setup_power_button (struct platform_device*) ; 
 int setup_sci_interrupt (struct platform_device*) ; 

__attribute__((used)) static int xo1_sci_probe(struct platform_device *pdev)
{
	struct resource *res;
	int r;

	/* don't run on non-XOs */
	if (!machine_is_olpc())
		return -ENODEV;

	r = mfd_cell_enable(pdev);
	if (r)
		return r;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!res) {
		dev_err(&pdev->dev, "can't fetch device resource info\n");
		return -EIO;
	}
	acpi_base = res->start;

	r = setup_power_button(pdev);
	if (r)
		return r;

	r = setup_ebook_switch(pdev);
	if (r)
		goto err_ebook;

	r = setup_lid_switch(pdev);
	if (r)
		goto err_lid;

	r = setup_lid_events();
	if (r)
		goto err_lidevt;

	r = setup_ec_sci();
	if (r)
		goto err_ecsci;

	/* Enable PME generation for EC-generated events */
	outl(CS5536_GPIOM6_PME_EN | CS5536_GPIOM7_PME_EN,
		acpi_base + CS5536_PM_GPE0_EN);

	/* Clear pending events */
	outl(0xffffffff, acpi_base + CS5536_PM_GPE0_STS);
	process_sci_queue(false);

	/* Initial sync */
	send_ebook_state();
	detect_lid_state();
	send_lid_state();

	r = setup_sci_interrupt(pdev);
	if (r)
		goto err_sci;

	/* Enable all EC events */
	olpc_ec_mask_write(EC_SCI_SRC_ALL);

	return r;

err_sci:
	free_ec_sci();
err_ecsci:
	free_lid_events();
err_lidevt:
	free_lid_switch();
err_lid:
	free_ebook_switch();
err_ebook:
	free_power_button();
	return r;
}