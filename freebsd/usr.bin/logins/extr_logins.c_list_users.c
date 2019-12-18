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
struct xpasswd {scalar_t__ pw_selected; } ;

/* Variables and functions */
 int /*<<< orphan*/  display_user (struct xpasswd*) ; 
 unsigned int npwds ; 
 struct xpasswd* pwds ; 

__attribute__((used)) static void
list_users(void)
{
	struct xpasswd *pwd;
	unsigned int i;

	for (i = 0, pwd = pwds; i < npwds; ++i, ++pwd)
		if (pwd->pw_selected)
			display_user(pwd);
}