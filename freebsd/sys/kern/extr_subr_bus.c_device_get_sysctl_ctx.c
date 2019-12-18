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
struct sysctl_ctx_list {int dummy; } ;
typedef  TYPE_1__* device_t ;
struct TYPE_3__ {struct sysctl_ctx_list sysctl_ctx; } ;

/* Variables and functions */

struct sysctl_ctx_list *
device_get_sysctl_ctx(device_t dev)
{
	return (&dev->sysctl_ctx);
}