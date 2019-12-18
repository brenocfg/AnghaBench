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
struct logininfo {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct logininfo* login_alloc_entry (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  login_free_entry (struct logininfo*) ; 
 int /*<<< orphan*/  login_logout (struct logininfo*) ; 

void
record_logout(pid_t pid, const char *tty, const char *user)
{
	struct logininfo *li;

	li = login_alloc_entry(pid, user, NULL, tty);
	login_logout(li);
	login_free_entry(li);
}