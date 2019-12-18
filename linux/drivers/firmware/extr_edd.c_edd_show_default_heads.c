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
struct TYPE_2__ {int /*<<< orphan*/  num_default_heads; } ;
struct edd_info {TYPE_1__ params; } ;
struct edd_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct edd_info* edd_dev_get_info (struct edd_device*) ; 
 int /*<<< orphan*/  left ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
edd_show_default_heads(struct edd_device *edev, char *buf)
{
	struct edd_info *info;
	char *p = buf;
	if (!edev)
		return -EINVAL;
	info = edd_dev_get_info(edev);
	if (!info || !buf)
		return -EINVAL;

	p += scnprintf(p, left, "%u\n", info->params.num_default_heads);
	return (p - buf);
}