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
struct evdev_dev {int /*<<< orphan*/  ev_serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAMELEN ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 

inline void
evdev_set_serial(struct evdev_dev *evdev, const char *serial)
{

	snprintf(evdev->ev_serial, NAMELEN, "%s", serial);
}