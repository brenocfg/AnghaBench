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
struct evdev_dev {int dummy; } ;
typedef  size_t int32_t ;

/* Variables and functions */
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * evdev_fngmap ; 
 int /*<<< orphan*/  evdev_support_key (struct evdev_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ *) ; 

void
evdev_support_nfingers(struct evdev_dev *evdev, int32_t nfingers)
{
	int32_t i;

	for (i = 0; i < MIN(nitems(evdev_fngmap), nfingers); i++)
		evdev_support_key(evdev, evdev_fngmap[i]);
}