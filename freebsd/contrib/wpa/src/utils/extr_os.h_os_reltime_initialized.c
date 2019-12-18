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
struct os_reltime {scalar_t__ sec; scalar_t__ usec; } ;

/* Variables and functions */

__attribute__((used)) static inline int os_reltime_initialized(struct os_reltime *t)
{
	return t->sec != 0 || t->usec != 0;
}