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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  _rs_stir () ; 
 scalar_t__ getpid () ; 
 size_t rs_count ; 
 int /*<<< orphan*/  rs_initialized ; 
 scalar_t__ rs_stir_pid ; 

__attribute__((used)) static inline void
_rs_stir_if_needed(size_t len)
{
	pid_t pid = getpid();

	if (rs_count <= len || !rs_initialized || rs_stir_pid != pid) {
		rs_stir_pid = pid;
		_rs_stir();
	} else
		rs_count -= len;
}