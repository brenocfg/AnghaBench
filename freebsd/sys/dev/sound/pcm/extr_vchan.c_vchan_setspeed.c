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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  maxspeed; } ;
struct vchan_info {TYPE_1__ caps; int /*<<< orphan*/  channel; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_LOCKASSERT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
vchan_setspeed(kobj_t obj, void *data, uint32_t speed)
{
	struct vchan_info *info;

	info = data;

	CHN_LOCKASSERT(info->channel);

	return (info->caps.maxspeed);
}