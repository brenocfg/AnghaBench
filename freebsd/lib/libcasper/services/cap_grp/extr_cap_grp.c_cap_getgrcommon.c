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
struct group {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int cap_getgrcommon_r (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct group**) ; 
 int errno ; 
 int /*<<< orphan*/  gbuffer ; 
 int /*<<< orphan*/  gbufsize ; 
 int /*<<< orphan*/  ggrp ; 

__attribute__((used)) static struct group *
cap_getgrcommon(cap_channel_t *chan, const char *cmd, const char *name,
    gid_t gid)
{
	struct group *result;
	int error, serrno;

	serrno = errno;

	error = cap_getgrcommon_r(chan, cmd, name, gid, &ggrp, gbuffer,
	    gbufsize, &result);
	if (error != 0) {
		errno = error;
		return (NULL);
	}

	errno = serrno;

	return (result);
}