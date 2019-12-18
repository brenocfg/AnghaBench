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
struct sta2x11_instance {int /*<<< orphan*/  list; scalar_t__ bus0; } ;
struct pci_dev {int /*<<< orphan*/  dev; TYPE_1__* subordinate; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int STA2X11_SWIOTLB_SIZE ; 
 int /*<<< orphan*/  dev_emerg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct sta2x11_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sta2x11_instance_list ; 
 scalar_t__ swiotlb_late_init_with_default_size (int) ; 

__attribute__((used)) static void sta2x11_new_instance(struct pci_dev *pdev)
{
	struct sta2x11_instance *instance;

	instance = kzalloc(sizeof(*instance), GFP_ATOMIC);
	if (!instance)
		return;
	/* This has a subordinate bridge, with 4 more-subordinate ones */
	instance->bus0 = pdev->subordinate->number + 1;

	if (list_empty(&sta2x11_instance_list)) {
		int size = STA2X11_SWIOTLB_SIZE;
		/* First instance: register your own swiotlb area */
		dev_info(&pdev->dev, "Using SWIOTLB (size %i)\n", size);
		if (swiotlb_late_init_with_default_size(size))
			dev_emerg(&pdev->dev, "init swiotlb failed\n");
	}
	list_add(&instance->list, &sta2x11_instance_list);
}