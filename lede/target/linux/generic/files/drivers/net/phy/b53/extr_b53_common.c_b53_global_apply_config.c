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
struct switch_dev {int dummy; } ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b53_apply (struct b53_device*) ; 
 int /*<<< orphan*/  b53_set_forwarding (struct b53_device*,int) ; 
 struct b53_device* sw_to_b53 (struct switch_dev*) ; 

__attribute__((used)) static int b53_global_apply_config(struct switch_dev *dev)
{
	struct b53_device *priv = sw_to_b53(dev);

	/* disable switching */
	b53_set_forwarding(priv, 0);

	b53_apply(priv);

	/* enable switching */
	b53_set_forwarding(priv, 1);

	return 0;
}