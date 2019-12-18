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
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  devctl_notify_f (char const*,char const*,char const*,char const*,int /*<<< orphan*/ ) ; 

void
devctl_notify(const char *system, const char *subsystem, const char *type,
    const char *data)
{

	devctl_notify_f(system, subsystem, type, data, M_NOWAIT);
}