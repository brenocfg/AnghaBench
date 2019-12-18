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
typedef  int /*<<< orphan*/  time_t ;
struct logininfo {int /*<<< orphan*/  tv_sec; int /*<<< orphan*/  hostname; } ;

/* Variables and functions */
 int /*<<< orphan*/  login_get_lastlog (struct logininfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

time_t
get_last_login_time(uid_t uid, const char *logname,
    char *buf, size_t bufsize)
{
	struct logininfo li;

	login_get_lastlog(&li, uid);
	strlcpy(buf, li.hostname, bufsize);
	return (time_t)li.tv_sec;
}