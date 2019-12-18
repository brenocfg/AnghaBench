#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct crypt_ctl {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NPE_QLEN ; 
 int /*<<< orphan*/  crypt_phys ; 
 int /*<<< orphan*/  crypt_virt ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* pdev ; 

__attribute__((used)) static int setup_crypt_desc(void)
{
	struct device *dev = &pdev->dev;
	BUILD_BUG_ON(sizeof(struct crypt_ctl) != 64);
	crypt_virt = dma_alloc_coherent(dev,
					NPE_QLEN * sizeof(struct crypt_ctl),
					&crypt_phys, GFP_ATOMIC);
	if (!crypt_virt)
		return -ENOMEM;
	return 0;
}