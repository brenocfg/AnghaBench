#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
typedef  void* u64 ;
typedef  void* u32 ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_3__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; scalar_t__ end; scalar_t__ start; } ;
struct TYPE_4__ {void* cookie2; void* cookie1; } ;
struct papr_scm_priv {int block_size; int blocks; int is_volatile; TYPE_2__ res; scalar_t__ bound_addr; struct platform_device* pdev; void* metadata_size; TYPE_1__ nd_set; void* drc_index; struct device_node* dn; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int H_OVERLAP ; 
 int H_SUCCESS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 void* cpu_to_le64 (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 int drc_pmem_bind (struct papr_scm_priv*) ; 
 int drc_pmem_query_n_bind (struct papr_scm_priv*) ; 
 int /*<<< orphan*/  drc_pmem_unbind (struct papr_scm_priv*) ; 
 int /*<<< orphan*/  kfree (struct papr_scm_priv*) ; 
 struct papr_scm_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,void**) ; 
 scalar_t__ of_property_read_u64 (struct device_node*,char*,void**) ; 
 int papr_scm_nvdimm_init (struct papr_scm_priv*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct papr_scm_priv*) ; 
 int /*<<< orphan*/  uuid_parse (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int papr_scm_probe(struct platform_device *pdev)
{
	struct device_node *dn = pdev->dev.of_node;
	u32 drc_index, metadata_size;
	u64 blocks, block_size;
	struct papr_scm_priv *p;
	const char *uuid_str;
	u64 uuid[2];
	int rc;

	/* check we have all the required DT properties */
	if (of_property_read_u32(dn, "ibm,my-drc-index", &drc_index)) {
		dev_err(&pdev->dev, "%pOF: missing drc-index!\n", dn);
		return -ENODEV;
	}

	if (of_property_read_u64(dn, "ibm,block-size", &block_size)) {
		dev_err(&pdev->dev, "%pOF: missing block-size!\n", dn);
		return -ENODEV;
	}

	if (of_property_read_u64(dn, "ibm,number-of-blocks", &blocks)) {
		dev_err(&pdev->dev, "%pOF: missing number-of-blocks!\n", dn);
		return -ENODEV;
	}

	if (of_property_read_string(dn, "ibm,unit-guid", &uuid_str)) {
		dev_err(&pdev->dev, "%pOF: missing unit-guid!\n", dn);
		return -ENODEV;
	}


	p = kzalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	/* optional DT properties */
	of_property_read_u32(dn, "ibm,metadata-size", &metadata_size);

	p->dn = dn;
	p->drc_index = drc_index;
	p->block_size = block_size;
	p->blocks = blocks;
	p->is_volatile = !of_property_read_bool(dn, "ibm,cache-flush-required");

	/* We just need to ensure that set cookies are unique across */
	uuid_parse(uuid_str, (uuid_t *) uuid);
	/*
	 * cookie1 and cookie2 are not really little endian
	 * we store a little endian representation of the
	 * uuid str so that we can compare this with the label
	 * area cookie irrespective of the endian config with which
	 * the kernel is built.
	 */
	p->nd_set.cookie1 = cpu_to_le64(uuid[0]);
	p->nd_set.cookie2 = cpu_to_le64(uuid[1]);

	/* might be zero */
	p->metadata_size = metadata_size;
	p->pdev = pdev;

	/* request the hypervisor to bind this region to somewhere in memory */
	rc = drc_pmem_bind(p);

	/* If phyp says drc memory still bound then force unbound and retry */
	if (rc == H_OVERLAP)
		rc = drc_pmem_query_n_bind(p);

	if (rc != H_SUCCESS) {
		dev_err(&p->pdev->dev, "bind err: %d\n", rc);
		rc = -ENXIO;
		goto err;
	}

	/* setup the resource for the newly bound range */
	p->res.start = p->bound_addr;
	p->res.end   = p->bound_addr + p->blocks * p->block_size - 1;
	p->res.name  = pdev->name;
	p->res.flags = IORESOURCE_MEM;

	rc = papr_scm_nvdimm_init(p);
	if (rc)
		goto err2;

	platform_set_drvdata(pdev, p);

	return 0;

err2:	drc_pmem_unbind(p);
err:	kfree(p);
	return rc;
}