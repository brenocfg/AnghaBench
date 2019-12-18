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
struct platform_device {int /*<<< orphan*/  name; } ;
struct kernel_param {int dummy; } ;
struct ipmi_plat_data {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; int /*<<< orphan*/  space; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  h ;
typedef  enum hotmod_op { ____Placeholder_hotmod_op } hotmod_op ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HM_ADD ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ dev_is_platform (struct device*) ; 
 int /*<<< orphan*/  hotmod_nr ; 
 int /*<<< orphan*/  ipmi_platform_add (char*,int /*<<< orphan*/ ,struct ipmi_plat_data*) ; 
 struct device* ipmi_si_remove_by_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ipmi_plat_data*,int /*<<< orphan*/ ,int) ; 
 int parse_hotmod_str (char*,int*,struct ipmi_plat_data*) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 unsigned int strlen (char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int hotmod_handler(const char *val, const struct kernel_param *kp)
{
	char *str = kstrdup(val, GFP_KERNEL), *curr, *next;
	int  rv;
	struct ipmi_plat_data h;
	unsigned int len;
	int ival;

	if (!str)
		return -ENOMEM;

	/* Kill any trailing spaces, as we can get a "\n" from echo. */
	len = strlen(str);
	ival = len - 1;
	while ((ival >= 0) && isspace(str[ival])) {
		str[ival] = '\0';
		ival--;
	}

	for (curr = str; curr; curr = next) {
		enum hotmod_op op;

		next = strchr(curr, ':');
		if (next) {
			*next = '\0';
			next++;
		}

		memset(&h, 0, sizeof(h));
		rv = parse_hotmod_str(curr, &op, &h);
		if (rv)
			goto out;

		if (op == HM_ADD) {
			ipmi_platform_add("hotmod-ipmi-si",
					  atomic_inc_return(&hotmod_nr),
					  &h);
		} else {
			struct device *dev;

			dev = ipmi_si_remove_by_data(h.space, h.type, h.addr);
			if (dev && dev_is_platform(dev)) {
				struct platform_device *pdev;

				pdev = to_platform_device(dev);
				if (strcmp(pdev->name, "hotmod-ipmi-si") == 0)
					platform_device_unregister(pdev);
			}
			if (dev)
				put_device(dev);
		}
	}
	rv = len;
out:
	kfree(str);
	return rv;
}