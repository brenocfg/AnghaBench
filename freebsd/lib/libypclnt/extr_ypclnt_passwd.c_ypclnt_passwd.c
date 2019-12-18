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
typedef  int /*<<< orphan*/  ypclnt_t ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int ypclnt_havepasswdd (int /*<<< orphan*/ *) ; 
 int yppasswd_local (int /*<<< orphan*/ *,struct passwd const*) ; 
 int yppasswd_remote (int /*<<< orphan*/ *,struct passwd const*,char const*) ; 

int
ypclnt_passwd(ypclnt_t *ypclnt, const struct passwd *pwd, const char *passwd)
{
	switch (ypclnt_havepasswdd(ypclnt)) {
	case 0:
		return (yppasswd_remote(ypclnt, pwd, passwd));
	case 1:
		return (yppasswd_local(ypclnt, pwd));
	default:
		return (-1);
	}
}