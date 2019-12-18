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
struct device {TYPE_1__* pins; scalar_t__ of_node_reused; } ;
struct TYPE_3__ {void* p; void* idle_state; void* sleep_state; void* init_state; void* default_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PINCTRL_STATE_DEFAULT ; 
 int /*<<< orphan*/  PINCTRL_STATE_IDLE ; 
 int /*<<< orphan*/  PINCTRL_STATE_INIT ; 
 int /*<<< orphan*/  PINCTRL_STATE_SLEEP ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,TYPE_1__*) ; 
 TYPE_1__* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_pinctrl_get (struct device*) ; 
 int /*<<< orphan*/  devm_pinctrl_put (void*) ; 
 void* pinctrl_lookup_state (void*,int /*<<< orphan*/ ) ; 
 int pinctrl_select_state (void*,void*) ; 

int pinctrl_bind_pins(struct device *dev)
{
	int ret;

	if (dev->of_node_reused)
		return 0;

	dev->pins = devm_kzalloc(dev, sizeof(*(dev->pins)), GFP_KERNEL);
	if (!dev->pins)
		return -ENOMEM;

	dev->pins->p = devm_pinctrl_get(dev);
	if (IS_ERR(dev->pins->p)) {
		dev_dbg(dev, "no pinctrl handle\n");
		ret = PTR_ERR(dev->pins->p);
		goto cleanup_alloc;
	}

	dev->pins->default_state = pinctrl_lookup_state(dev->pins->p,
					PINCTRL_STATE_DEFAULT);
	if (IS_ERR(dev->pins->default_state)) {
		dev_dbg(dev, "no default pinctrl state\n");
		ret = 0;
		goto cleanup_get;
	}

	dev->pins->init_state = pinctrl_lookup_state(dev->pins->p,
					PINCTRL_STATE_INIT);
	if (IS_ERR(dev->pins->init_state)) {
		/* Not supplying this state is perfectly legal */
		dev_dbg(dev, "no init pinctrl state\n");

		ret = pinctrl_select_state(dev->pins->p,
					   dev->pins->default_state);
	} else {
		ret = pinctrl_select_state(dev->pins->p, dev->pins->init_state);
	}

	if (ret) {
		dev_dbg(dev, "failed to activate initial pinctrl state\n");
		goto cleanup_get;
	}

#ifdef CONFIG_PM
	/*
	 * If power management is enabled, we also look for the optional
	 * sleep and idle pin states, with semantics as defined in
	 * <linux/pinctrl/pinctrl-state.h>
	 */
	dev->pins->sleep_state = pinctrl_lookup_state(dev->pins->p,
					PINCTRL_STATE_SLEEP);
	if (IS_ERR(dev->pins->sleep_state))
		/* Not supplying this state is perfectly legal */
		dev_dbg(dev, "no sleep pinctrl state\n");

	dev->pins->idle_state = pinctrl_lookup_state(dev->pins->p,
					PINCTRL_STATE_IDLE);
	if (IS_ERR(dev->pins->idle_state))
		/* Not supplying this state is perfectly legal */
		dev_dbg(dev, "no idle pinctrl state\n");
#endif

	return 0;

	/*
	 * If no pinctrl handle or default state was found for this device,
	 * let's explicitly free the pin container in the device, there is
	 * no point in keeping it around.
	 */
cleanup_get:
	devm_pinctrl_put(dev->pins->p);
cleanup_alloc:
	devm_kfree(dev, dev->pins);
	dev->pins = NULL;

	/* Return deferrals */
	if (ret == -EPROBE_DEFER)
		return ret;
	/* Return serious errors */
	if (ret == -EINVAL)
		return ret;
	/* We ignore errors like -ENOENT meaning no pinctrl state */

	return 0;
}