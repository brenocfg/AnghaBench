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
struct spacc_engine {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct spacc_engine* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static inline struct spacc_engine *spacc_dev_to_engine(struct device *dev)
{
	return dev ? dev_get_drvdata(dev) : NULL;
}