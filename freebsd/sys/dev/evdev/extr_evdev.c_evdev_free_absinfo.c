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
struct input_absinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_EVDEV ; 
 int /*<<< orphan*/  free (struct input_absinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evdev_free_absinfo(struct input_absinfo *absinfo)
{

	free(absinfo, M_EVDEV);
}