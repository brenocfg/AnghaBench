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
struct sockaddr {int dummy; } ;
struct logininfo {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct logininfo* login_alloc_entry (int /*<<< orphan*/ ,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  login_free_entry (struct logininfo*) ; 
 int /*<<< orphan*/  login_login (struct logininfo*) ; 
 int /*<<< orphan*/  login_set_addr (struct logininfo*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_lastlog_message (char const*,int /*<<< orphan*/ ) ; 

void
record_login(pid_t pid, const char *tty, const char *user, uid_t uid,
    const char *host, struct sockaddr *addr, socklen_t addrlen)
{
	struct logininfo *li;

	/* save previous login details before writing new */
	store_lastlog_message(user, uid);

	li = login_alloc_entry(pid, user, host, tty);
	login_set_addr(li, addr, addrlen);
	login_login(li);
	login_free_entry(li);
}