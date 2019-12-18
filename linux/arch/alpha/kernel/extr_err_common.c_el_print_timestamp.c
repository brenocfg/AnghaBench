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
struct TYPE_2__ {int /*<<< orphan*/  second; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  year; int /*<<< orphan*/  day; int /*<<< orphan*/  month; } ;
union el_timestamp {TYPE_1__ b; scalar_t__ as_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
el_print_timestamp(union el_timestamp *timestamp)
{
	if (timestamp->as_int)
		printk("%s  TIMESTAMP: %d/%d/%02d %d:%02d:%0d\n", 
		       err_print_prefix,
		       timestamp->b.month, timestamp->b.day,
		       timestamp->b.year, timestamp->b.hour,
		       timestamp->b.minute, timestamp->b.second);
}