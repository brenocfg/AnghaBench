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
struct monitor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  monitor_openfds (struct monitor*,int) ; 
 struct monitor* xcalloc (int,int) ; 

struct monitor *
monitor_init(void)
{
	struct monitor *mon;

	mon = xcalloc(1, sizeof(*mon));
	monitor_openfds(mon, 1);

	return mon;
}