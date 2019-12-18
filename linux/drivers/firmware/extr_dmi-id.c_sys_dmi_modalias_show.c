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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 size_t get_modalias (char*,scalar_t__) ; 

__attribute__((used)) static ssize_t sys_dmi_modalias_show(struct device *dev,
				     struct device_attribute *attr, char *page)
{
	ssize_t r;
	r = get_modalias(page, PAGE_SIZE-1);
	page[r] = '\n';
	page[r+1] = 0;
	return r+1;
}