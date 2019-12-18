#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct d40_chan {TYPE_2__ chan; } ;
struct TYPE_3__ {struct device device; } ;

/* Variables and functions */

__attribute__((used)) static struct device *chan2dev(struct d40_chan *d40c)
{
	return &d40c->chan.dev->device;
}