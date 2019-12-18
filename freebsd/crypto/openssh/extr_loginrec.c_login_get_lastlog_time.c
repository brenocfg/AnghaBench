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
typedef  int /*<<< orphan*/  uid_t ;
struct logininfo {unsigned int tv_sec; } ;

/* Variables and functions */
 scalar_t__ login_get_lastlog (struct logininfo*,int /*<<< orphan*/  const) ; 

unsigned int
login_get_lastlog_time(const uid_t uid)
{
	struct logininfo li;

	if (login_get_lastlog(&li, uid))
		return (li.tv_sec);
	else
		return (0);
}