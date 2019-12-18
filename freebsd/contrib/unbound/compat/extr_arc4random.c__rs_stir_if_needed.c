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
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {size_t rs_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rs_stir () ; 
 scalar_t__ getpid () ; 
 TYPE_1__* rs ; 

__attribute__((used)) static inline void
_rs_stir_if_needed(size_t len)
{
#ifndef MAP_INHERIT_ZERO
	static pid_t _rs_pid = 0;
	pid_t pid = getpid();

	/* If a system lacks MAP_INHERIT_ZERO, resort to getpid() */
	if (_rs_pid == 0 || _rs_pid != pid) {
		_rs_pid = pid;
		if (rs)
			rs->rs_count = 0;
	}
#endif
	if (!rs || rs->rs_count <= len)
		_rs_stir();
	if (rs->rs_count <= len)
		rs->rs_count = 0;
	else
		rs->rs_count -= len;
}