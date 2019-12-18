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

/* Variables and functions */
 int /*<<< orphan*/  do_write_blocked (void const*,unsigned long) ; 
 int /*<<< orphan*/  finish_record () ; 

__attribute__((used)) static void write_blocked(const void *data, unsigned long size)
{
	do_write_blocked(data, size);
	finish_record();
}