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
struct passwd {char* pw_class; scalar_t__ pw_uid; } ;
typedef  int /*<<< orphan*/  login_cap_t ;

/* Variables and functions */
 char* LOGIN_DEFCLASS ; 
 char* LOGIN_DEFROOTCLASS ; 
 int /*<<< orphan*/ * login_getclassbyname (char const*,struct passwd const*) ; 

login_cap_t *
login_getpwclass(const struct passwd *pwd)
{
    const char	*cls = NULL;

    if (pwd != NULL) {
	cls = pwd->pw_class;
	if (cls == NULL || *cls == '\0')
	    cls = (pwd->pw_uid == 0) ? LOGIN_DEFROOTCLASS : LOGIN_DEFCLASS;
    }
    /*
     * XXX: pwd should be unused by login_getclassbyname() unless cls is `me',
     *      so NULL can be passed instead of pwd for more safety.
     */
    return login_getclassbyname(cls, pwd);
}