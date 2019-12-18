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
typedef  size_t uint16_t ;
struct evdev_dev {int* ev_rep; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t REP_CNT ; 

inline void
evdev_set_repeat_params(struct evdev_dev *evdev, uint16_t property, int value)
{

	KASSERT(property < REP_CNT, ("invalid evdev repeat property"));
	evdev->ev_rep[property] = value;
}