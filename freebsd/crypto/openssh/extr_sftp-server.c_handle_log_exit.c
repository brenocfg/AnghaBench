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
typedef  size_t u_int ;
struct TYPE_2__ {scalar_t__ use; } ;

/* Variables and functions */
 scalar_t__ HANDLE_UNUSED ; 
 int /*<<< orphan*/  handle_log_close (size_t,char*) ; 
 TYPE_1__* handles ; 
 size_t num_handles ; 

__attribute__((used)) static void
handle_log_exit(void)
{
	u_int i;

	for (i = 0; i < num_handles; i++)
		if (handles[i].use != HANDLE_UNUSED)
			handle_log_close(i, "forced");
}