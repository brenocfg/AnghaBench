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
struct si_sm_io {scalar_t__ addr_space; scalar_t__ addr_data; scalar_t__ regspacing; } ;
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_REGSPACING ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IPMI_IO_ADDR_SPACE ; 
 scalar_t__ IPMI_MEM_ADDR_SPACE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct resource *
ipmi_get_info_from_resources(struct platform_device *pdev,
			     struct si_sm_io *io)
{
	struct resource *res, *res_second;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (res) {
		io->addr_space = IPMI_IO_ADDR_SPACE;
	} else {
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
		if (res)
			io->addr_space = IPMI_MEM_ADDR_SPACE;
	}
	if (!res) {
		dev_err(&pdev->dev, "no I/O or memory address\n");
		return NULL;
	}
	io->addr_data = res->start;

	io->regspacing = DEFAULT_REGSPACING;
	res_second = platform_get_resource(pdev,
			       (io->addr_space == IPMI_IO_ADDR_SPACE) ?
					IORESOURCE_IO : IORESOURCE_MEM,
			       1);
	if (res_second) {
		if (res_second->start > io->addr_data)
			io->regspacing = res_second->start - io->addr_data;
	}

	return res;
}