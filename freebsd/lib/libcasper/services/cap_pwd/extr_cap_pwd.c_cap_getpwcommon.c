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
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int cap_getpwcommon_r (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct passwd**) ; 
 int errno ; 
 int /*<<< orphan*/  gbuffer ; 
 int /*<<< orphan*/  gbufsize ; 
 int /*<<< orphan*/  gpwd ; 

__attribute__((used)) static struct passwd *
cap_getpwcommon(cap_channel_t *chan, const char *cmd, const char *login,
    uid_t uid)
{
	struct passwd *result;
	int error, serrno;

	serrno = errno;

	error = cap_getpwcommon_r(chan, cmd, login, uid, &gpwd, gbuffer,
	    gbufsize, &result);
	if (error != 0) {
		errno = error;
		return (NULL);
	}

	errno = serrno;

	return (result);
}