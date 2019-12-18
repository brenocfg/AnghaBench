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
struct os_reltime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 int /*<<< orphan*/  os_reltime_sub (struct os_reltime*,struct os_reltime*,struct os_reltime*) ; 

__attribute__((used)) static inline void os_reltime_age(struct os_reltime *start,
				  struct os_reltime *age)
{
	struct os_reltime now;

	os_get_reltime(&now);
	os_reltime_sub(&now, start, age);
}