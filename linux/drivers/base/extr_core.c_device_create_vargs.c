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
typedef  int /*<<< orphan*/  va_list ;
struct device {int dummy; } ;
struct class {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 struct device* device_create_groups_vargs (struct class*,struct device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

struct device *device_create_vargs(struct class *class, struct device *parent,
				   dev_t devt, void *drvdata, const char *fmt,
				   va_list args)
{
	return device_create_groups_vargs(class, parent, devt, drvdata, NULL,
					  fmt, args);
}