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
typedef  int /*<<< orphan*/  u32 ;
struct sbridge_pvt {int dummy; } ;
typedef  enum dev_type { ____Placeholder_dev_type } dev_type ;

/* Variables and functions */
 int DEV_UNKNOWN ; 

__attribute__((used)) static enum dev_type sbridge_get_width(struct sbridge_pvt *pvt, u32 mtr)
{
	/* there's no way to figure out */
	return DEV_UNKNOWN;
}