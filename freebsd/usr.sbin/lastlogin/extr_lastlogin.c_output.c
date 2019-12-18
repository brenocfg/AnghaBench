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
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;
struct utmpx {int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_user; TYPE_1__ ut_tv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctime (scalar_t__*) ; 
 int /*<<< orphan*/  xo_attr (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 

__attribute__((used)) static void
output(struct utmpx *u)
{
	time_t t = u->ut_tv.tv_sec;

	xo_open_instance("lastlogin");
	xo_emit("{:user/%-10s/%s} {:tty/%-8s/%s} {:from/%-22.22s/%s}",
		u->ut_user, u->ut_line, u->ut_host);
	xo_attr("seconds", "%lu", (unsigned long)t);
	xo_emit(" {:login-time/%.24s/%.24s}\n", ctime(&t));
	xo_close_instance("lastlogin");
}