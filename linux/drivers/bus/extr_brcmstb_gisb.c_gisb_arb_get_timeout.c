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
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct brcmstb_gisb_arb_device {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_TIMER ; 
 struct brcmstb_gisb_arb_device* dev_get_drvdata (struct device*) ; 
 int gisb_read (struct brcmstb_gisb_arb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t gisb_arb_get_timeout(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct brcmstb_gisb_arb_device *gdev = dev_get_drvdata(dev);
	u32 timeout;

	mutex_lock(&gdev->lock);
	timeout = gisb_read(gdev, ARB_TIMER);
	mutex_unlock(&gdev->lock);

	return sprintf(buf, "%d", timeout);
}