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
struct table_info {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,...) ; 

__attribute__((used)) static void
ta_print_kfib_config(void *ta_state, struct table_info *ti, char *buf,
    size_t bufsize)
{

	if (ti->data != 0)
		snprintf(buf, bufsize, "%s fib=%lu", "addr:kfib", ti->data);
	else
		snprintf(buf, bufsize, "%s", "addr:kfib");
}