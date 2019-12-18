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
struct os_reltime {int sec; int usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 int /*<<< orphan*/  os_reltime_sub (struct os_reltime*,struct os_reltime*,struct os_reltime*) ; 

__attribute__((used)) static int ms_from_time(struct os_reltime *last)
{
	struct os_reltime now, res;

	os_get_reltime(&now);
	os_reltime_sub(&now, last, &res);
	return res.sec * 1000 + res.usec / 1000;
}