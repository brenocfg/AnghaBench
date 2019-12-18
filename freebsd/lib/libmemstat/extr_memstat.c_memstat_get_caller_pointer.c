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
struct memory_type {void** mt_caller_pointer; } ;

/* Variables and functions */

void *
memstat_get_caller_pointer(const struct memory_type *mtp, int index)
{

	return (mtp->mt_caller_pointer[index]);
}