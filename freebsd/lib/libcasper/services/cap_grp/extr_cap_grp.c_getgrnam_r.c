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
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int cap_getgrcommon_r (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,struct group*,char*,size_t,struct group**) ; 

int
cap_getgrnam_r(cap_channel_t *chan, const char *name, struct group *grp,
    char *buffer, size_t bufsize, struct group **result)
{

	return (cap_getgrcommon_r(chan, "getgrnam_r", name, 0, grp, buffer,
	    bufsize, result));
}