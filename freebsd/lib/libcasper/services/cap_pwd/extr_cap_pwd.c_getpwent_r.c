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
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int cap_getpwcommon_r (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct passwd*,char*,size_t,struct passwd**) ; 

int
cap_getpwent_r(cap_channel_t *chan, struct passwd *pwd, char *buffer,
    size_t bufsize, struct passwd **result)
{

	return (cap_getpwcommon_r(chan, "getpwent_r", NULL, 0, pwd, buffer,
	    bufsize, result));
}