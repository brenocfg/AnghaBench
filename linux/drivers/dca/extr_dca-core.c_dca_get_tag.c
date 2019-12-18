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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dca_common_get_tag (struct device*,int) ; 

u8 dca_get_tag(int cpu)
{
	struct device *dev = NULL;

	return dca_common_get_tag(dev, cpu);
}