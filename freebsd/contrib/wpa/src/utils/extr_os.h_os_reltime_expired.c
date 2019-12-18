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
typedef  scalar_t__ os_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_reltime_sub (struct os_reltime*,struct os_reltime*,struct os_reltime*) ; 

__attribute__((used)) static inline int os_reltime_expired(struct os_reltime *now,
				     struct os_reltime *ts,
				     os_time_t timeout_secs)
{
	struct os_reltime age;

	os_reltime_sub(now, ts, &age);
	return (age.sec > timeout_secs) ||
	       (age.sec == timeout_secs && age.usec > 0);
}