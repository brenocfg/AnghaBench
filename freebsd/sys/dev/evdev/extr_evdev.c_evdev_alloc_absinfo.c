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
 int ABS_CNT ; 
 int /*<<< orphan*/  M_EVDEV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct input_absinfo* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct input_absinfo *
evdev_alloc_absinfo(void)
{

	return (malloc(sizeof(struct input_absinfo) * ABS_CNT, M_EVDEV,
	    M_WAITOK | M_ZERO));
}