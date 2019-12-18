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
typedef  scalar_t__ mode_t ;
typedef  int /*<<< orphan*/  login_cap_t ;

/* Variables and functions */
 unsigned long LOGIN_SETCPUMASK ; 
 unsigned long LOGIN_SETENV ; 
 unsigned long LOGIN_SETPATH ; 
 unsigned long LOGIN_SETRESOURCES ; 
 unsigned long LOGIN_SETUMASK ; 
 scalar_t__ login_getcapnum (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  setclasscpumask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setclassenvironment (int /*<<< orphan*/ *,struct passwd const*,int) ; 
 int /*<<< orphan*/  setclassresources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mode_t
setlogincontext(login_cap_t *lc, const struct passwd *pwd,
		mode_t mymask, unsigned long flags)
{
    if (lc) {
	/* Set resources */
	if (flags & LOGIN_SETRESOURCES)
	    setclassresources(lc);
	/* See if there's a umask override */
	if (flags & LOGIN_SETUMASK)
	    mymask = (mode_t)login_getcapnum(lc, "umask", mymask, mymask);
	/* Set paths */
	if (flags & LOGIN_SETPATH)
	    setclassenvironment(lc, pwd, 1);
	/* Set environment */
	if (flags & LOGIN_SETENV)
	    setclassenvironment(lc, pwd, 0);
	/* Set cpu affinity */
	if (flags & LOGIN_SETCPUMASK)
	    setclasscpumask(lc);
    }
    return (mymask);
}