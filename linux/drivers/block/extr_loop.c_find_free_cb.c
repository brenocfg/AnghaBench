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
struct loop_device {scalar_t__ lo_state; } ;

/* Variables and functions */
 scalar_t__ Lo_unbound ; 

__attribute__((used)) static int find_free_cb(int id, void *ptr, void *data)
{
	struct loop_device *lo = ptr;
	struct loop_device **l = data;

	if (lo->lo_state == Lo_unbound) {
		*l = lo;
		return 1;
	}
	return 0;
}