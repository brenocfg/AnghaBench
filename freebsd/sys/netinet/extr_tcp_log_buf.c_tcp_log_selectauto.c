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
 int atomic_fetchadd_long (int /*<<< orphan*/ *,int) ; 
 int tcp_log_auto_ratio ; 
 int /*<<< orphan*/  tcp_log_auto_ratio_cur ; 

__attribute__((used)) static __inline bool
tcp_log_selectauto(void)
{

	/*
	 * If we are doing auto-capturing, figure out whether we will capture
	 * this session.
	 */
	if (tcp_log_auto_ratio &&
	    (atomic_fetchadd_long(&tcp_log_auto_ratio_cur, 1) %
	    tcp_log_auto_ratio) == 0)
		return (true);
	return (false);
}