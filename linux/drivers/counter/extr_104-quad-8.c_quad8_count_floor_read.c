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
struct counter_device {int dummy; } ;
struct counter_count {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t quad8_count_floor_read(struct counter_device *counter,
	struct counter_count *count, void *private, char *buf)
{
	/* Only a floor of 0 is supported */
	return sprintf(buf, "0\n");
}