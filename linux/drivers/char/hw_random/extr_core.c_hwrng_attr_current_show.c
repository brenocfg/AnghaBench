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
struct hwrng {char* name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct hwrng*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PTR_ERR (struct hwrng*) ; 
 struct hwrng* get_current_rng () ; 
 int /*<<< orphan*/  put_rng (struct hwrng*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t hwrng_attr_current_show(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	ssize_t ret;
	struct hwrng *rng;

	rng = get_current_rng();
	if (IS_ERR(rng))
		return PTR_ERR(rng);

	ret = snprintf(buf, PAGE_SIZE, "%s\n", rng ? rng->name : "none");
	put_rng(rng);

	return ret;
}