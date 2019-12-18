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
struct dump_args {int /*<<< orphan*/  cnt; } ;

/* Variables and functions */

__attribute__((used)) static int
count_ext_entries(void *e, void *arg)
{
	struct dump_args *da;

	da = (struct dump_args *)arg;
	da->cnt++;

	return (0);
}