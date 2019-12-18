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
struct rtl8366_smi {struct device* parent; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct rtl8366_smi* kzalloc (int,int /*<<< orphan*/ ) ; 

struct rtl8366_smi *rtl8366_smi_alloc(struct device *parent)
{
	struct rtl8366_smi *smi;

	BUG_ON(!parent);

	smi = kzalloc(sizeof(*smi), GFP_KERNEL);
	if (!smi) {
		dev_err(parent, "no memory for private data\n");
		return NULL;
	}

	smi->parent = parent;
	return smi;
}