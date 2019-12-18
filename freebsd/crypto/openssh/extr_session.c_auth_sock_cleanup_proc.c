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
struct passwd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_sock_dir ; 
 int /*<<< orphan*/ * auth_sock_name ; 
 int /*<<< orphan*/  restore_uid () ; 
 int /*<<< orphan*/  rmdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temporarily_use_uid (struct passwd*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
auth_sock_cleanup_proc(struct passwd *pw)
{
	if (auth_sock_name != NULL) {
		temporarily_use_uid(pw);
		unlink(auth_sock_name);
		rmdir(auth_sock_dir);
		auth_sock_name = NULL;
		restore_uid();
	}
}