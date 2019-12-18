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
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct n2_crypto {int /*<<< orphan*/  cwq_list; int /*<<< orphan*/  cwq_info; } ;
struct mdesc_handle {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HV_NCS_QTYPE_CWQ ; 
 struct n2_crypto* alloc_n2cp () ; 
 int /*<<< orphan*/  cpu_to_cwq ; 
 int /*<<< orphan*/  cwq_intr ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct n2_crypto*) ; 
 int /*<<< orphan*/  free_n2cp (struct n2_crypto*) ; 
 int grab_global_resources () ; 
 int grab_mdesc_irq_props (struct mdesc_handle*,struct platform_device*,int /*<<< orphan*/ *,char*) ; 
 struct mdesc_handle* mdesc_grab () ; 
 int /*<<< orphan*/  mdesc_release (struct mdesc_handle*) ; 
 int n2_register_algs () ; 
 int /*<<< orphan*/  n2_spu_driver_version () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_global_resources () ; 
 int /*<<< orphan*/  spu_list_destroy (int /*<<< orphan*/ *) ; 
 int spu_mdesc_scan (struct mdesc_handle*,struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int n2_crypto_probe(struct platform_device *dev)
{
	struct mdesc_handle *mdesc;
	struct n2_crypto *np;
	int err;

	n2_spu_driver_version();

	pr_info("Found N2CP at %pOF\n", dev->dev.of_node);

	np = alloc_n2cp();
	if (!np) {
		dev_err(&dev->dev, "%pOF: Unable to allocate n2cp.\n",
			dev->dev.of_node);
		return -ENOMEM;
	}

	err = grab_global_resources();
	if (err) {
		dev_err(&dev->dev, "%pOF: Unable to grab global resources.\n",
			dev->dev.of_node);
		goto out_free_n2cp;
	}

	mdesc = mdesc_grab();

	if (!mdesc) {
		dev_err(&dev->dev, "%pOF: Unable to grab MDESC.\n",
			dev->dev.of_node);
		err = -ENODEV;
		goto out_free_global;
	}
	err = grab_mdesc_irq_props(mdesc, dev, &np->cwq_info, "n2cp");
	if (err) {
		dev_err(&dev->dev, "%pOF: Unable to grab IRQ props.\n",
			dev->dev.of_node);
		mdesc_release(mdesc);
		goto out_free_global;
	}

	err = spu_mdesc_scan(mdesc, dev, &np->cwq_info, &np->cwq_list,
			     "cwq", HV_NCS_QTYPE_CWQ, cwq_intr,
			     cpu_to_cwq);
	mdesc_release(mdesc);

	if (err) {
		dev_err(&dev->dev, "%pOF: CWQ MDESC scan failed.\n",
			dev->dev.of_node);
		goto out_free_global;
	}

	err = n2_register_algs();
	if (err) {
		dev_err(&dev->dev, "%pOF: Unable to register algorithms.\n",
			dev->dev.of_node);
		goto out_free_spu_list;
	}

	dev_set_drvdata(&dev->dev, np);

	return 0;

out_free_spu_list:
	spu_list_destroy(&np->cwq_list);

out_free_global:
	release_global_resources();

out_free_n2cp:
	free_n2cp(np);

	return err;
}